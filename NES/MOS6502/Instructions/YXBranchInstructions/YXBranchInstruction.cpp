#include "YXBranchInstruction.h"
#include "../DecodeHelper.h"

using namespace mos6502;


YXBranchInstruction::YXBranchInstruction
(
	uint8_t caValue,
	uint8_t bValue,
	Word PC,
	Byte lowOrderOperand,
	Byte highOrderOperand
) :
	instruction(static_cast<YXBranchInstructions>(caValue)),
	decodeMode(static_cast<YXBranchInstructionAddressingMode>(bValue)),
	PC(PC),
	lowOrderOperand(lowOrderOperand),
	highOrderOperand(highOrderOperand),
	instructionSize(0),
	decodeVal(0),
	address(0),
	executeVal(0),
	memoryVal(0)
{
	
}

void YXBranchInstruction::decode
(
	RegisterMap& registerMap,
	MemoryAccessor& memory
)
{
	
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