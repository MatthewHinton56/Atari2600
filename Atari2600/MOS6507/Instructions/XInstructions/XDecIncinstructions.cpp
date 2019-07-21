#include "XDecIncIntructions.h"
#include "../DecodeHelper.h"

using namespace mos6507;


XDecIncInstruction::XDecIncInstruction
(
	uint8_t caValue,
	uint8_t bValue,
	Word PC,
	Byte lowOrderOperand,
	Byte highOrderOperand
) :
	instruction(static_cast<XDecIncInstructions>(caValue)),
	decodeMode(static_cast<InstructionAddressingMode>(bValue)),
	PC(PC),
	lowOrderOperand(lowOrderOperand),
	highOrderOperand(highOrderOperand),
	instructionSize(InstructionSizes[decodeMode]),
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
		decodeMode = (decodeMode == InstructionAddressingMode::xZeroPage) ? InstructionAddressingMode::yIndirect : decodeMode;
		decodeMode = (decodeMode == InstructionAddressingMode::absoluteX) ? InstructionAddressingMode::absoluteY : decodeMode;

	}

	decodeMode = (decodeMode == InstructionAddressingMode::xIndirect) ? InstructionAddressingMode::immediate : decodeMode;
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

			case XDecIncInstructions::iTxs:
				address = 0;
				decodeVal = registerMap["X"];
				break;

			case XDecIncInstructions::iTsx:
				address = 0;
				decodeVal = registerMap["SP"];
				break;

			case XDecIncInstructions::iDex:
				address = 0;
				decodeVal = registerMap["X"];
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
		registerVal = (decodeMode == InstructionAddressingMode::absoluteX) ? registerMap["X"] : registerMap["Y"];
		address = absolute(memory, lowOrderOperand, highOrderOperand, registerVal, crossedPage);
		cycles += (crossedPage) ? 1 : 0;
		break;

	case InstructionAddressingMode::yZeroPage:
	case InstructionAddressingMode::xZeroPage:
	case InstructionAddressingMode::zeroPage:
		registerVal = (decodeMode == InstructionAddressingMode::zeroPage) ? 0 : registerMap["X"];
		registerVal = (decodeMode == InstructionAddressingMode::yZeroPage) ? registerMap["Y"] : registerVal;
		address = zeroPage(lowOrderOperand, registerVal);
		break;

	case InstructionAddressingMode::xIndirect:
		registerVal = registerMap["X"];
		address = xIndirect(memory, lowOrderOperand, registerVal);
		break;

	case InstructionAddressingMode::yIndirect:
		registerVal = registerMap["Y"];
		address = yIndirect(memory, lowOrderOperand, registerVal, crossedPage);
		cycles += (crossedPage) ? 1 : 0;
		break;

	default:
		throw std::invalid_argument("Address Mode not Supported");

	}

	if (instruction != XDecIncInstructions::iStx)
		decodeVal = memory[address];
	else
		decodeVal = registerMap["X"];

}

void mos6507::XDecIncInstruction::execute(RegisterMap& registerMap)
{
	/*switch (instruction)
	{
		case XDecIncInstructions::iDec:
				
	}*/
}

void mos6507::XDecIncInstruction::writeBack(RegisterMap& registerMap, MemoryAccessor& memory)
{
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
