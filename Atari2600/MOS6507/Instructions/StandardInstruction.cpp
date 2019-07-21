#include "StandardInstruction.h"
#include "Binary.h"

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
	instructionSize(InstructionSizes[decodeMode]),
	decodeVal(0),
	address(0),
	executeVal(0),
	memoryVal(0)
{
	if (specialMode && decodeMode == InstructionAddressingMode::immediate)
		instructionSize = 1;

	cycles = (specialMode) ? specialCycleTimes[decodeMode] : 2 + cycleTimes[decodeMode];
}

void StandardInstruction::decode
(
	RegisterMap& registerMap, 
	MemoryAccessor& memory
)
{
	//Special Mode - A mode and different cycles
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

	if(instruction != StandardInstructions::iSta)
		decodeVal = memory[address];
}

void StandardInstruction::execute(RegisterMap& registerMap)
{
	//Byte statusRegister = registerMap["SR"];
	switch (instruction)
	{
		case StandardInstructions::iSbc:
		case StandardInstructions::iCmp:
		case StandardInstructions::iAdc:
			executeVal = (getDecimalFlag(registerMap["SR"])) ?
				airthmenticBCD(arithmeticFunctions[instruction], registerMap["A"], decodeVal, registerMap["SR"]) :
				airthmentic(arithmeticFunctions[instruction], registerMap["A"], decodeVal, registerMap["SR"]);
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
			executeVal = decodeVal;
			break;

		case StandardInstructions::iSta:
			break;
	}
}

void StandardInstruction::writeBack
(
	RegisterMap& registerMap, 
	MemoryAccessor& memory
)
{

	if (instruction == StandardInstructions::iSta)
	{
		memory[address] = registerMap["A"];
	}
	else if(!specialMode || decodeMode == InstructionAddressingMode::immediate)
	{
		registerMap["A"] = executeVal;
	}
	else
	{
		memory[address] = executeVal;
	}
}

Word StandardInstruction::pc()
{
	return PC + instructionSize;
}

Byte mos6507::StandardInstruction::getDecodeVal() const
{
	return decodeVal;
}

Word mos6507::StandardInstruction::getAddress() const
{
	return address;
}

Byte mos6507::StandardInstruction::getExceuteVal() const
{
	return executeVal;
}

Byte mos6507::StandardInstruction::getMemoryVal() const
{
	return memoryVal;
}

Word mos6507::StandardInstruction::getPC() const
{
	return PC;
}

unsigned int mos6507::StandardInstruction::getInstructionSize() const
{
	return instructionSize;
}

unsigned int mos6507::StandardInstruction::getCycles() const
{
	return cycles;
}
