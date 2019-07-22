#include "StandardInstruction.h"
#include "../Binary.h"
#include "../DecodeHelper.h"

using namespace mos6507;

StandardInstruction::StandardInstruction
(
	uint8_t caValue, 
	uint8_t bValue,
	Word PC, 
	Byte lowOrderOperand, 
	Byte highOrderOperand
) :
	instruction(static_cast<StandardInstructions>(caValue)),
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
	cycles = (instruction >= static_cast<StandardInstructions>(020)) ?
		specialCycleTimes[decodeMode] :
		2 + cycleTimes[decodeMode];

	if (instruction >= static_cast<StandardInstructions>(020) && decodeMode == InstructionAddressingMode::immediate)
	{
		decodeMode = InstructionAddressingMode::implied;
		instructionSize = 1;
	}
}

void StandardInstruction::decode
(
	RegisterMap& registerMap, 
	MemoryAccessor& memory
)
{
	//Special Mode - A mode and different cycles
	Byte registerVal;

	if (decodeMode == InstructionAddressingMode::immediate)
	{
		decodeVal = lowOrderOperand;
		return;
	}

	if (decodeMode == InstructionAddressingMode::implied)
	{
		decodeVal = registerMap["A"];
		return;
	}

	bool crossedPage = false;

	switch (decodeMode)
	{
		case InstructionAddressingMode::absolute:
			address = absolute(memory, lowOrderOperand, highOrderOperand);
			break;

		case InstructionAddressingMode::absoluteY:
		case InstructionAddressingMode::absoluteX:
			registerVal = (decodeMode == InstructionAddressingMode::absoluteX) ? registerMap["X"] : registerMap["Y"];
			address = absolute(memory, lowOrderOperand, highOrderOperand, registerVal, crossedPage);
			cycles += (crossedPage && instruction < static_cast<StandardInstructions>(020)) ? 1 : 0;
			break;

		case InstructionAddressingMode::xZeroPage:
		case InstructionAddressingMode::zeroPage:
			registerVal = (decodeMode == InstructionAddressingMode::zeroPage) ? 0 : registerMap["X"];
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
	}

	if (instruction != StandardInstructions::iSta)
		decodeVal = memory[address];
	else
		decodeVal = registerMap["A"];
}

void StandardInstruction::execute(RegisterMap& registerMap)
{
	//Byte statusRegister = registerMap["SR"];
	switch (instruction)
	{
		case StandardInstructions::iSbc:
		case StandardInstructions::iCmp:
		case StandardInstructions::iAdc:
			executeVal = arithmetic(arithmeticFunctions[instruction], registerMap["A"], decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iOra:
		case StandardInstructions::iEor:
		case StandardInstructions::iAnd:
			executeVal = logic(logicFunctions[instruction], registerMap["A"], decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iRor:
		case StandardInstructions::iRol:
		case StandardInstructions::iLsr:
		case StandardInstructions::iAsl:
			executeVal = shift(shiftFunctions[instruction], decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iLda:
			examine(decodeVal, registerMap["SR"]);
		case StandardInstructions::iSta:
			executeVal = decodeVal;
			break;
	}
}

void StandardInstruction::writeBack
(
	RegisterMap& registerMap, 
	MemoryAccessor& memory
)
{
	bool specialMode = instruction >= static_cast<StandardInstructions>(020);
	if (instruction == StandardInstructions::iSta || (specialMode && decodeMode != InstructionAddressingMode::implied))
	{
		memory[address] = executeVal;
	}
	else
	{
		registerMap["A"] = executeVal;
	}

}

Word StandardInstruction::pc()
{
	return PC + instructionSize;
}

Byte StandardInstruction::getDecodeVal() const
{
	return decodeVal;
}

Word StandardInstruction::getAddress() const
{
	return address;
}

Byte StandardInstruction::getExceuteVal() const
{
	return executeVal;
}

Byte StandardInstruction::getMemoryVal() const
{
	return memoryVal;
}

Word StandardInstruction::getPC() const
{
	return PC;
}

unsigned int StandardInstruction::getInstructionSize() const
{
	return instructionSize;
}

unsigned int StandardInstruction::getCycles() const
{
	return cycles;
}
