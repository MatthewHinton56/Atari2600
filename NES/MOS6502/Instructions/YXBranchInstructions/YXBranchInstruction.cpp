#include "YXBranchInstruction.h"
#include "YXBranchInstructionConstants.h"
#include "../DecodeHelper.h"
#include "../Binary.h"

using namespace mos6502;


YXBranchInstruction::YXBranchInstruction
(
	uint8_t aValue,
	uint8_t bValue,
	uint8_t cValue,
	Word PC,
	Byte lowOrderOperand,
	Byte highOrderOperand
) :
	instruction(YXBHexToInstructions[generateABC(aValue, bValue, cValue)]),
	decodeMode(static_cast<YXBranchInstructionAddressingMode>(bValue)),
	PC(PC),
	lowOrderOperand(lowOrderOperand),
	highOrderOperand(highOrderOperand),
	decodeVal(0),
	address(0),
	executeVal(0),
	memoryVal(0),
	instructionSize(0),
	cycles(0),
	branch(0)
{
	decodeMode = (decodeMode == YXBranchInstructionAddressingMode::impl_two) ?
		YXBranchInstructionAddressingMode::implied :
		decodeMode;

	instructionSize = (YXBInstructionSizes[decodeMode]);
	cycles = (YXBcycleTimes[decodeMode]);
} 

void YXBranchInstruction::decode
(
	RegisterMap& registerMap,
	MemoryAccessor& memory
)
{
	//Special Mode - A mode and different cycles
	Byte registerVal;

	if (decodeMode == YXBranchInstructionAddressingMode::immediate || decodeMode == YXBranchInstructionAddressingMode::relative)
	{
		decodeVal = lowOrderOperand;

		return;
	}

	if (decodeMode == YXBranchInstructionAddressingMode::implied)
	{
		switch (instruction)
		{
			case YXBranchInstructions::iIny:
			case YXBranchInstructions::iDey:
			case YXBranchInstructions::iTya:
				decodeVal = registerMap[Y];
				break;

			case YXBranchInstructions::iTay:
				decodeVal = registerMap[AC];
				break;

			case YXBranchInstructions::iInx:
				decodeVal = registerMap[X];
				break;
		}
		return;
	}

	bool crossedPage = false;

	switch (decodeMode)
	{
	case YXBranchInstructionAddressingMode::absolute:
		address = absolute(memory, lowOrderOperand, highOrderOperand);
		break;

	case YXBranchInstructionAddressingMode::absoluteX:
		registerVal = (decodeMode == YXBranchInstructionAddressingMode::absoluteX) ? registerMap[X] : registerMap[Y];
		address = absolute(memory, lowOrderOperand, highOrderOperand, registerVal, crossedPage);
		cycles += (crossedPage) ? 1 : 0;
		break;

	case YXBranchInstructionAddressingMode::xZeroPage:
	case YXBranchInstructionAddressingMode::zeroPage:
		registerVal = (decodeMode == YXBranchInstructionAddressingMode::zeroPage) ? 0 : registerMap[X];
		address = zeroPage(lowOrderOperand, registerVal);
		break;
	}

	if (instruction != YXBranchInstructions::iSty)
		decodeVal = memory[address];
	else
		decodeVal = registerMap[Y];
}

void mos6502::YXBranchInstruction::execute(RegisterMap& registerMap)
{
	switch (instruction)
	{
		case YXBranchInstructions::iBcc:
			executeVal = (getCarryFlag(registerMap[SR])) ? 0 : decodeVal;
			break;
		
		case YXBranchInstructions::iBcs:
			executeVal = (getCarryFlag(registerMap[SR])) ? decodeVal : 0;
			break;

		case YXBranchInstructions::iBeq:
			executeVal = (getZeroFlag(registerMap[SR])) ? decodeVal : 0;
			break;

		case YXBranchInstructions::iBne:
			executeVal = (getZeroFlag(registerMap[SR])) ? 0 : decodeVal;
			break;
		
		case YXBranchInstructions::iCld:
			clearDecimalFlag(registerMap[SR]);
			break;

		case YXBranchInstructions::iClv:
			clearOverflowFlag(registerMap[SR]);
			break;

		case YXBranchInstructions::iCpx:
			executeVal = arithmetic(ArithmeticOperator::CMP, registerMap[X], decodeVal, registerMap[SR]);
			break;

		case YXBranchInstructions::iCpy:
			executeVal = arithmetic(ArithmeticOperator::CMP, registerMap[Y], decodeVal, registerMap[SR]);
			break;

		case YXBranchInstructions::iDey:
			executeVal = dec(registerMap[Y], registerMap[SR]);
			break;

		case YXBranchInstructions::iInx:
			executeVal = inc(registerMap[X], registerMap[SR]);
			break;

		case YXBranchInstructions::iIny:
			executeVal = inc(registerMap[Y], registerMap[SR]);
			break;

		case YXBranchInstructions::iSed:
			setDecimalFlag(registerMap[SR]);
			break;

		case YXBranchInstructions::iLdy:
		case YXBranchInstructions::iTay:
		case YXBranchInstructions::iTya:
			examine(decodeVal, registerMap[SR]);
		case YXBranchInstructions::iSty:
			executeVal = decodeVal;
			break;
	}

	if (decodeMode == YXBranchInstructionAddressingMode::relative)
	{
		if (executeVal != 0)
		{
			Word oldPage = (PC + instructionSize) & 0xFF00;

			Word newPage = (PC + instructionSize + (int8_t)executeVal) & 0xFF00;

			cycles += (newPage != oldPage) ? 2 : 1;
		}
	}


}

void mos6502::YXBranchInstruction::writeBack(RegisterMap& registerMap, MemoryAccessor& memory)
{
	switch (instruction)
	{
	case YXBranchInstructions::iIny:
	case YXBranchInstructions::iDey:
	case YXBranchInstructions::iTay:
	case YXBranchInstructions::iLdy:
	case YXBranchInstructions::iCpy:
		registerMap[Y] = executeVal;
		break;

	case YXBranchInstructions::iTya:
		registerMap[AC] = executeVal;
		break;

	case YXBranchInstructions::iInx:
	case YXBranchInstructions::iCpx:
		registerMap[X] = executeVal;
		break;

	case YXBranchInstructions::iSty:
		memory[address] = executeVal;
		break;

	case YXBranchInstructions::iBcc:
	case YXBranchInstructions::iBcs:
	case YXBranchInstructions::iBeq:
	case YXBranchInstructions::iBne:
		branch = executeVal;
		break;
	}
}

Word YXBranchInstruction::pc()
{
	return PC + instructionSize + (int8_t)branch;
}

Byte YXBranchInstruction::getDecodeVal() const
{
	return decodeVal;
}

Word YXBranchInstruction::getAddress() const
{
	return address;
}

Byte YXBranchInstruction::getExceuteVal() const
{
	return executeVal;
}

Byte YXBranchInstruction::getMemoryVal() const
{
	return memoryVal;
}

Word YXBranchInstruction::getPC() const
{
	return PC;
}

unsigned int YXBranchInstruction::getInstructionSize() const
{
	return instructionSize;
}

unsigned int YXBranchInstruction::getCycles() const
{
	return cycles;
}

YXBranchInstructions YXBranchInstruction::getInstruction() const
{
	return instruction;
}

YXBranchInstructionAddressingMode YXBranchInstruction::getDecodeMode() const
{
	return decodeMode;
}
