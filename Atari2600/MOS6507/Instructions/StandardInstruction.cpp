#include "StandardInstruction.h"
#include "Binary.h"
#include "BCD.h"

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
	instructionSize(InstructionSizes[decodeMode]),
	decodeVal(0),
	address(0),
	executeVal(0),
	memoryVal(0)
{
	if (specialMode && decodeMode == InstructionAddressingMode::immediate)
		instructionSize = 1;
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

	if(instruction != StandardInstructions::iSta)
		decodeVal = memory[address];
}

void StandardInstruction::execute(RegisterMap registerMap)
{
	Byte statusRegister = registerMap["SR"];
	switch (instruction)
	{
		case StandardInstructions::iAdc:
			executeVal = (getDecimalFlag(statusRegister)) ? 
				addWithCarryBCD(registerMap["A"], decodeVal, registerMap["SR"]) : 
				addWithCarry(registerMap["A"], decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iAnd:
			executeVal = logic(LogicOperator::AND, registerMap["A"], decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iAsl:
			executeVal = shift(ShiftOperator::ASL, decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iCmp:
			compare(registerMap["A"], decodeVal, registerMap["SR"]);
			executeVal = registerMap["A"];
			break;

		case StandardInstructions::iEor:
			executeVal = logic(LogicOperator::XOR, registerMap["A"], decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iLda:
			executeVal = decodeVal;
			break;

		case StandardInstructions::iLsr:
			executeVal = shift(ShiftOperator::LSR, decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iOra:
			executeVal = logic(LogicOperator::OR, registerMap["A"], decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iRol:
			executeVal = shift(ShiftOperator::ROL, decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iRor:
			executeVal = shift(ShiftOperator::ROR, decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iSbc:
			executeVal = (getDecimalFlag(statusRegister)) ?
			subtractWithCarryBCD(registerMap["A"], decodeVal, registerMap["SR"]) :
			subtractWithCarry(registerMap["A"], decodeVal, registerMap["SR"]);
			break;

		case StandardInstructions::iSta:
			break;
	}
}

void StandardInstruction::writeBack(MemoryAccessor& memory, RegisterMap& registerMap)
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

Byte mos6507::StandardInstruction::getExceuteVal() const
{
	return executeVal;
}

Byte mos6507::StandardInstruction::getMemoryVal() const
{
	return memoryVal;
}

Byte mos6507::StandardInstruction::getPC() const
{
	return PC;
}

Byte mos6507::StandardInstruction::getInstructionSize() const
{
	return instructionSize;
}

Byte mos6507::StandardInstruction::getCycles() const
{
	return cycles;
}
