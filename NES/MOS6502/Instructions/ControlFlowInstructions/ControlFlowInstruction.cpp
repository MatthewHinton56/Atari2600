#include "ControlFlowInstruction.h"
#include "ControlFlowInstructionConstants.h"
#include "../DecodeHelper.h"
#include "../Binary.h"

using namespace mos6502;


ControlFlowInstruction::ControlFlowInstruction
(
	uint8_t aValue,
	uint8_t bValue,
	uint8_t cValue,
	Word PC,
	Word newPC,
	Byte lowOrderOperand,
	Byte highOrderOperand
) :
	instruction(CFHexToInstructions[generateABC(aValue, bValue, cValue)]),
	decodeMode(static_cast<ControlFlowInstructionAddressingMode>(bValue)),
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

	instructionSize = (ControlFlowInstructionSizes[decodeMode]);
	cycles = (CFHexToCycleTime[generateABC(aValue, bValue, cValue)]);
}

void ControlFlowInstruction::decode
(
	RegisterMap& registerMap,
	MemoryAccessor& memory
)
{
	//Special Mode - A mode and different cycles
	Byte registerVal;

	if (decodeMode == ControlFlowInstructionAddressingMode::relative)
	{
		decodeVal = lowOrderOperand;

		return;
	}

	if (decodeMode == ControlFlowInstructionAddressingMode::implied)
	{
		switch (instruction)
		{
			case ControlFlowInstructions::iBrk:
				newPC = memory.readWord(IRQ_VECTOR);
				break;

			case ControlFlowInstructions::iPhp:
				decodeVal = registerMap["SR"];
				break;

			case ControlFlowInstructions::iPla:
			case ControlFlowInstructions::iPlp:
				decodeVal = memory[registerMap["SP"]];
				break;

			case ControlFlowInstructions::iRti:
				decodeVal = memory[address];
				newPC = memory.readWord(address + 2);
				break;

			case ControlFlowInstructions::iPha:
				decodeVal = registerMap["A"];
				break;

			case ControlFlowInstructions::iRts:
				newPC = memory.readWord(address);
				break;

		}
		return;
	}

	switch (decodeMode)
	{
	case ControlFlowInstructionAddressingMode::absolute:
		address = absolute(memory, lowOrderOperand, highOrderOperand);
		break;

	case ControlFlowInstructionAddressingMode::zeroPage:
		registerVal = (decodeMode == ControlFlowInstructionAddressingMode::zeroPage) ? 0 : registerMap["X"];
		address = zeroPage(lowOrderOperand, registerVal);
		break;

	case ControlFlowInstructionAddressingMode::indirect:
		address = indirect(memory, lowOrderOperand, highOrderOperand);
	}

	if (instruction != ControlFlowInstructions::iJmp && instruction != ControlFlowInstructions::iJsr)
		decodeVal = memory[address];
	else
		newPC = memory.readWord(address);

}

void mos6502::ControlFlowInstruction::execute(RegisterMap& registerMap)
{
	switch (instruction)
	{
		case ControlFlowInstructions::iBit:
			(decodeVal & 0x80) ? setNegativeFlag(registerMap["SR"]) : clearNegativeFlag(registerMap["SR"]);
			(decodeVal & 0x40) ? setOverflowFlag(registerMap["SR"]) : clearOverflowFlag(registerMap["SR"]);
			(decodeVal & registerMap["A"]) ? clearZeroFlag(registerMap["SR"]) : setZeroFlag(registerMap["SR"]);
			break;

		case ControlFlowInstructions::iBmi:
			executeVal = (getNegativeFlag(registerMap["SR"])) ? decodeVal : 0;
			break;

		case ControlFlowInstructions::iBpl:
			executeVal = (getNegativeFlag(registerMap["SR"])) ?  0 : decodeVal;
			break;
		
		case ControlFlowInstructions::iBvc:
			executeVal = (getOverflowFlag(registerMap["SR"])) ? 0 : decodeVal;;
			break;

		case ControlFlowInstructions::iBvs:
			executeVal = (getOverflowFlag(registerMap["SR"])) ? decodeVal : 0;
			break;

		case ControlFlowInstructions::iClc:
			clearCarryFlag(registerMap["SR"]);
			break;

		case ControlFlowInstructions::iCli:
			clearInterruptFlag(registerMap["SR"]);
			break;

		case ControlFlowInstructions::iSec:
			setCarryFlag(registerMap["SR"]);
			break;

		case ControlFlowInstructions::iSei:
			setInterruptFlag(registerMap["SR"]);
			break;
	}

	if (decodeMode == ControlFlowInstructionAddressingMode::relative)
	{
		if (executeVal != 0)
		{
			Word oldPage = (PC + instructionSize) & 0xFF00;

			Word newPage = (PC + instructionSize + (int8_t)executeVal) & 0xFF00;

			cycles += (newPage != oldPage) ? 2 : 1;
		}
	}


}

void mos6502::ControlFlowInstruction::writeBack(RegisterMap& registerMap, MemoryAccessor& memory)
{
	switch (instruction)
	{
		case ControlFlowInstructions::iBvc:
		case ControlFlowInstructions::iBvs:
		case ControlFlowInstructions::iBmi:
		case ControlFlowInstructions::iBpl:
		branch = executeVal;
		break;

	}
}

Word ControlFlowInstruction::pc()
{
	return PC + instructionSize + (int8_t)branch;
}

Byte ControlFlowInstruction::getDecodeVal() const
{
	return decodeVal;
}

Word ControlFlowInstruction::getAddress() const
{
	return address;
}

Byte ControlFlowInstruction::getExceuteVal() const
{
	return executeVal;
}

Byte ControlFlowInstruction::getMemoryVal() const
{
	return memoryVal;
}

Word ControlFlowInstruction::getPC() const
{
	return PC;
}

unsigned int ControlFlowInstruction::getInstructionSize() const
{
	return instructionSize;
}

unsigned int ControlFlowInstruction::getCycles() const
{
	return cycles;
}

ControlFlowInstructions ControlFlowInstruction::getInstruction() const
{
	return instruction;
}

ControlFlowInstructionAddressingMode ControlFlowInstruction::getDecodeMode() const
{
	return decodeMode;
}
