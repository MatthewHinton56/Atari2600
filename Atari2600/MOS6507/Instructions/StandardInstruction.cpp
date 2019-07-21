#include "StandardInstruction.h"

using namespace mos6507;

StandardInstruction::StandardInstruction
(
	uint8_t caValue, 
	InstructionAddressingMode decodeMode,
	Word PC, 
	Byte lowOrderOperand, 
	Byte highOrderOperand
) :
	instruction(static_cast<StandardInstructions>(caValue)),
	decodeMode(decodeMode),
	specialMode(instruction >= static_cast<StandardInstructions>(020)),
	PC(PC),
	lowOrderOperand(lowOrderOperand),
	highOrderOperand(highOrderOperand),
	cycles(0),
	instructionSize(0),
	decodeVal(0),
	address(0),
	executeVal(0),
	memoryVal(0)
{

}

void StandardInstruction::decode
(
	RegisterMap& registerMap, 
	MemoryAccessor& memory
)
{
	//Special Mode - A mode and different cycles
	cycles = (specialMode) ? specialCycleTimes[decodeMode] : cycleTimes[decodeMode];
	Byte registerVal;
	address;

	if (decodeMode == InstructionAddressingMode::immediate)
	{
		decodeVal = (specialMode) ? registerMap["Accumulator"] : lowOrderOperand;;
		return;
	}

	Word page;
	Word newPage;

	switch (decodeMode)
	{
		case InstructionAddressingMode::absolute:
			address = highOrderOperand << 8 | lowOrderOperand;
			break;

		case InstructionAddressingMode::absoluteY:
		case InstructionAddressingMode::absoluteX:
			registerVal = (decodeMode == InstructionAddressingMode::absoluteX) ? registerMap["X"] : registerMap["Y"];
			address = highOrderOperand << 8 | lowOrderOperand;
			address += registerVal;

			page = memory.getMemory().getPageMask() & address;
			newPage = memory.getMemory().getPageMask() & address;
			cycles += (newPage != page) ? 1 : 0;
			break;

		case InstructionAddressingMode::xZeroPage:
		case InstructionAddressingMode::zeroPage:
			registerVal = (decodeMode == InstructionAddressingMode::zeroPage) ? 0 : registerMap["Y"];
			address = registerVal + lowOrderOperand;
			break;

		case InstructionAddressingMode::xIndirect:
			registerVal = registerMap["X"];
			address = memory.xIndexIndirect(lowOrderOperand, registerVal);
			break;

		case InstructionAddressingMode::yIndirect:
			registerVal = registerMap["Y"];
			bool crossedPage;
			address = memory.yIndexIndirect(lowOrderOperand, registerVal, crossedPage);
			cycles += (crossedPage) ? 1 : 0;
			break;
	}

	if(instruction != StandardInstructions::iLda && instruction != StandardInstructions::iSta)
		decodeVal = memory[address];
}

void StandardInstruction::execute()
{
}

void mos6507::StandardInstruction::memory(MemoryAccessor& memory)
{
}

void StandardInstruction::writeBack(RegisterMap& registerMap)
{
}

void StandardInstruction::pc(Word& PC)
{
}

Byte mos6507::StandardInstruction::getDecodeVal() const
{
	return Byte();
}

Byte mos6507::StandardInstruction::getExceuteVal() const
{
	return Byte();
}

Byte mos6507::StandardInstruction::getMemoryVal() const
{
	return Byte();
}

Byte mos6507::StandardInstruction::getPC() const
{
	return Byte();
}

Byte mos6507::StandardInstruction::getInstructionSize() const
{
	return Byte();
}

Byte mos6507::StandardInstruction::getCycles() const
{
	return Byte();
}
