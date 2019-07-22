#include "YXBranchInstruction.h"
#include "YXBranchInstructionConstants.h"
#include "../DecodeHelper.h"

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
	instructionSize(InstructionSizes[decodeMode]),
	cycles(cycleTimes[decodeMode])
{
	decodeMode = (decodeMode == YXBranchInstructionAddressingMode::impl_two) ?
		YXBranchInstructionAddressingMode::implied :
		decodeMode;
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
		decodeVal = registerMap["A"];
		return;
	}

	bool crossedPage = false;

	switch (decodeMode)
	{
	case YXBranchInstructionAddressingMode::absolute:
		address = absolute(memory, lowOrderOperand, highOrderOperand);
		break;

	case YXBranchInstructionAddressingMode::absoluteX:
		registerVal = (decodeMode == YXBranchInstructionAddressingMode::absoluteX) ? registerMap["X"] : registerMap["Y"];
		address = absolute(memory, lowOrderOperand, highOrderOperand, registerVal, crossedPage);
		cycles += (crossedPage) ? 1 : 0;
		break;

	case YXBranchInstructionAddressingMode::xZeroPage:
	case YXBranchInstructionAddressingMode::zeroPage:
		registerVal = (decodeMode == YXBranchInstructionAddressingMode::zeroPage) ? 0 : registerMap["X"];
		address = zeroPage(lowOrderOperand, registerVal);
		break;
	}

	if (instruction != YXBranchInstructions::iSty)
		decodeVal = memory[address];
	else
		decodeVal = registerMap["A"];
}

void mos6502::YXBranchInstruction::execute(RegisterMap& registerMap)
{
	
}

void mos6502::YXBranchInstruction::writeBack(RegisterMap& registerMap, MemoryAccessor& memory)
{
	
}

Word YXBranchInstruction::pc()
{
	return PC + instructionSize;
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