#include "XDecIncInstruction.h"
#include "../DecodeHelper.h"

using namespace mos6502;


XDecIncInstruction::XDecIncInstruction
(
	uint8_t aValue,
	uint8_t bValue,
	uint8_t cValue,
	Word PC,
	Byte lowOrderOperand,
	Byte highOrderOperand
) :
	instruction(static_cast<XDecIncInstructions>(generateCA(aValue, cValue))),
	decodeMode(static_cast<InstructionAddressingMode>(bValue)),
	PC(PC),
	lowOrderOperand(lowOrderOperand),
	highOrderOperand(highOrderOperand),
	instructionSize(0),
	decodeVal(0),
	address(0),
	executeVal(0),
	memoryVal(0)
{
	if (decodeMode == InstructionAddressingMode::immediate)
	{
		instruction = (instruction == XDecIncInstructions::iStx) ? XDecIncInstructions::iTxa : instruction;
		instruction = (instruction == XDecIncInstructions::iLdx) ? XDecIncInstructions::iTax : instruction;
		instruction = (instruction == XDecIncInstructions::iDec) ? XDecIncInstructions::iDex : instruction;
		instruction = (instruction == XDecIncInstructions::iInc) ? XDecIncInstructions::iNop : instruction;
	}

	if (decodeMode == InstructionAddressingMode::absoluteY)
	{
		instruction = (instruction == XDecIncInstructions::iStx) ? XDecIncInstructions::iTxs : instruction;
		instruction = (instruction == XDecIncInstructions::iLdx) ? XDecIncInstructions::iTsx : instruction;
	}

	if (decodeMode == InstructionAddressingMode::immediate || decodeMode == InstructionAddressingMode::absoluteY)
	{
		decodeMode = InstructionAddressingMode::implied;
	}

	if (instruction == XDecIncInstructions::iStx || instruction == XDecIncInstructions::iLdx)
	{
		decodeMode = (decodeMode == InstructionAddressingMode::xIndirect) ? InstructionAddressingMode::immediate : decodeMode;
		decodeMode = (decodeMode == InstructionAddressingMode::xZeroPage) ? InstructionAddressingMode::yZeroPage : decodeMode;
		decodeMode = (decodeMode == InstructionAddressingMode::absoluteX) ? InstructionAddressingMode::absoluteY : decodeMode;

	}

	switch (instruction)
	{
		case XDecIncInstructions::iDec:
		case XDecIncInstructions::iInc:
			cycles = incDecCycleTimes[decodeMode];
			break;

		case XDecIncInstructions::iLdx:
			cycles = ldxCycleTimes[decodeMode];
			break;

		case XDecIncInstructions::iStx:
			cycles = stxCycleTimes[decodeMode];
			break;

		default:
			cycles = 2;
			break;
	}

	instructionSize = InstructionSizes[decodeMode];

}

void XDecIncInstruction::decode
(
	RegisterMap& registerMap,
	MemoryAccessor& memory
)
{
	//Special Mode - A mode and different cycles
	Byte registerVal;

	bool crossedPage = false;

	if (decodeMode == InstructionAddressingMode::immediate)
	{
		decodeVal = lowOrderOperand;
		address = 0;
		return;
	}

	if (decodeMode == InstructionAddressingMode::implied)
	{
		switch (instruction)
		{
		case XDecIncInstructions::iNop:
			address = 0;
			decodeVal = 0;
			break;

		case XDecIncInstructions::iTxa:
		case XDecIncInstructions::iTxs:
			address = 0;
			decodeVal = registerMap[X];
			break;

		case XDecIncInstructions::iTsx:
			address = 0;
			decodeVal = registerMap[SP];
			break;

		case XDecIncInstructions::iTax:
			address = 0;
			decodeVal = registerMap[AC];
			break;

		case XDecIncInstructions::iDex:
			address = 0;
			decodeVal = registerMap[X];
			break;
		}
		return;
	}

	switch (decodeMode)
	{
		case InstructionAddressingMode::absolute:
			address = absolute(memory, lowOrderOperand, highOrderOperand);
			break;

		case InstructionAddressingMode::absoluteY:
		case InstructionAddressingMode::absoluteX:
			registerVal = (decodeMode == InstructionAddressingMode::absoluteX) ? registerMap[X] : registerMap[Y];
			address = absolute(memory, lowOrderOperand, highOrderOperand, registerVal, crossedPage);
			cycles += (crossedPage && instruction == XDecIncInstructions::iLdx) ? 1 : 0;
			break;

		case InstructionAddressingMode::yZeroPage:
		case InstructionAddressingMode::xZeroPage:
		case InstructionAddressingMode::zeroPage:
			registerVal = (decodeMode == InstructionAddressingMode::zeroPage) ? 0 : registerMap[X];
			registerVal = (decodeMode == InstructionAddressingMode::yZeroPage) ? registerMap[Y] : registerVal;
			address = zeroPage(lowOrderOperand, registerVal);
			break;

		case InstructionAddressingMode::xIndirect:
			registerVal = registerMap[X];
			address = xIndirect(memory, lowOrderOperand, registerVal);
			break;

		case InstructionAddressingMode::yIndirect:
			registerVal = registerMap[Y];
			address = yIndirect(memory, lowOrderOperand, registerVal, crossedPage);
			cycles += (crossedPage) ? 1 : 0;
			break;

		default:
			throw std::invalid_argument("Address Mode not Supported");

	}

	if (instruction != XDecIncInstructions::iStx)
		decodeVal = memory[address];
	else
		decodeVal = registerMap[X];

}

void mos6502::XDecIncInstruction::execute(RegisterMap& registerMap)
{
	switch (instruction)
	{
		case XDecIncInstructions::iDex:
		case XDecIncInstructions::iDec:
			executeVal = dec(decodeVal, registerMap[SR]);
			break;

		case XDecIncInstructions::iInc:
			executeVal = inc(decodeVal, registerMap[SR]);
			break;

		case XDecIncInstructions::iTxa:
		case XDecIncInstructions::iLdx:
		case XDecIncInstructions::iTax:
		case XDecIncInstructions::iTsx:
			examine(decodeVal, registerMap[SR]);
		case XDecIncInstructions::iNop:
		case XDecIncInstructions::iTxs:
		case XDecIncInstructions::iStx:
			executeVal = decodeVal;
			break;
	}
}

void mos6502::XDecIncInstruction::writeBack(RegisterMap& registerMap, MemoryAccessor& memory)
{
	switch (instruction)
	{

		case XDecIncInstructions::iTax:
		case XDecIncInstructions::iLdx:
		case XDecIncInstructions::iTsx:
		case XDecIncInstructions::iDex:
			registerMap[X] = executeVal;
			break;

		case XDecIncInstructions::iStx:
		case XDecIncInstructions::iInc:
		case XDecIncInstructions::iDec:
			memory[address] = executeVal;
			break;

		case XDecIncInstructions::iTxs:
			registerMap[SP] = executeVal;
			break;
		case XDecIncInstructions::iTxa:
			registerMap[AC] = executeVal;
			break;

		case XDecIncInstructions::iNop:
			break;
	}
}

Word XDecIncInstruction::pc()
{
	return PC + instructionSize;
}

Byte XDecIncInstruction::getDecodeVal() const
{
	return decodeVal;
}

Word XDecIncInstruction::getAddress() const
{
	return address;
}

Byte XDecIncInstruction::getExceuteVal() const
{
	return executeVal;
}

Byte XDecIncInstruction::getMemoryVal() const
{
	return memoryVal;
}

Word XDecIncInstruction::getPC() const
{
	return PC;
}

unsigned int XDecIncInstruction::getInstructionSize() const
{
	return instructionSize;
}

unsigned int XDecIncInstruction::getCycles() const
{
	return cycles;
}

XDecIncInstructions XDecIncInstruction::getInstruction() const
{
	return instruction;
}

InstructionAddressingMode XDecIncInstruction::getDecodeMode() const
{
	return decodeMode;
}

Instructions mos6502::XDecIncInstruction::getInstructionType() const
{
	return Instructions::xDecIncInstructions;
}
