#include "SpecialInstruction.h"
#include "SpecialInstructionConstants.h"
#include "../DecodeHelper.h"
#include "../Binary.h"

using namespace mos6502;


SpecialInstruction::SpecialInstruction
(
	SpecialInstructions instruction,
	Word PC
) :
	instruction(instruction),
	decodeMode(instructionToDecodeMode[instruction]),
	PC(PC),
	newPC(),
	lowOrderOperand(0),
	highOrderOperand(0),
	decodeVal(0),
	address(0),
	executeVal(0),
	memoryVal(0),
	instructionSize(0),
	branch(0)
{

	instructionSize = (SInstructionSizes[instruction]);
	cycles = (ScycleTimes[instruction]);
}

void SpecialInstruction::decode
(
	RegisterMap& registerMap,
	MemoryAccessor& memory
)
{

	if (decodeMode == SpecialInstructionAddressingMode::implied)
	{
		switch (instruction)
		{
			case SpecialInstructions::iBrkNmi:
				newPC = memory.readWord(NMI_VECTOR);
				break;

			case SpecialInstructions::iBrkIrq:
				newPC = memory.readWord(IRQ_VECTOR);
				break;
		}
		return;
	}

}

void mos6502::SpecialInstruction::execute(RegisterMap& registerMap)
{
	switch (instruction)
	{

		case SpecialInstructions::iBrkIrq:
		case SpecialInstructions::iBrkNmi:
			executeVal = registerMap[SP] - 3;
			break;

	}

}

void mos6502::SpecialInstruction::writeBack(RegisterMap& registerMap, MemoryAccessor& memory)
{
	switch (instruction)
	{
		case SpecialInstructions::iBrkIrq:
		case SpecialInstructions::iBrkNmi:
			memory.writeWord(0x100 | (executeVal + 1), PC + instructionSize);
			memory[0x100 | executeVal] = registerMap[SR];
			registerMap[SP] = executeVal;
			setInterruptFlag(registerMap[SR]);
			break;
	}
}

Word SpecialInstruction::pc()
{
	switch (instruction)
	{
	case SpecialInstructions::iBrkNmi:
	case SpecialInstructions::iBrkIrq:
		return newPC;

	default:
		return PC + instructionSize + (int8_t)branch;
	}
}

Byte SpecialInstruction::getDecodeVal() const
{
	return decodeVal;
}

Word SpecialInstruction::getAddress() const
{
	return address;
}

Byte SpecialInstruction::getExceuteVal() const
{
	return executeVal;
}

Byte SpecialInstruction::getMemoryVal() const
{
	return memoryVal;
}

Word SpecialInstruction::getPC() const
{
	return PC;
}

unsigned int SpecialInstruction::getInstructionSize() const
{
	return instructionSize;
}

unsigned int SpecialInstruction::getCycles() const
{
	return cycles;
}

SpecialInstructions SpecialInstruction::getInstruction() const
{
	return instruction;
}

SpecialInstructionAddressingMode SpecialInstruction::getDecodeMode() const
{
	return decodeMode;
}

Instructions mos6502::SpecialInstruction::getInstructionType() const
{
	return Instructions::specialInstructions;
}
