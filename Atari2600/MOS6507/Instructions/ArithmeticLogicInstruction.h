#pragma once
#include "../MemoryAccessor.h"
#include "../MOS6507Constants.h"
#include "Instruction.h"
#include "InstructionConstants.h"

namespace mos6507
{
	class ArithmeticLogicInstruction : Instruction
	{
	public:

		ArithmeticLogicInstruction
		(
			uint8_t caValue,
			instructionAddressingMode,
			Word PC,
			Word operand = 0,
			Word registerOperand = 0
		);


		virtual void decode
		(
			RegisterMap& registerMap, 
			MemoryAccessor& memory
		);

		virtual void execute();

		virtual void memory(MemoryAccessor& memory);

		virtual void writeBack(RegisterMap& registerMap);

		virtual void pc(Word& PC);

	protected:

		arithmeticLogicInstructions instruction;
		instructionAddressingMode decodeMode;

		Word operand;
		Byte registerOperand;

		Word valE;
		Word PC;
		Word instructionSize;
		Word cycles;
	};
}
