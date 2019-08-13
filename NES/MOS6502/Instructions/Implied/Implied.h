#pragma once
#include "../Instruction.h"
#include "ImpliedConstants.h"

namespace mos6502
{
	class Implied
	{
	public:

		Implied
		(
			Byte opcode
		);

		virtual int32_t step
		(
			Word& PC,
			RegisterMap& registerMap, 
			Memory<PAGE_SIZE, NUM_PAGES>& mem
		);

		int32_t getStepCount() const { return stepCount; }
		Byte getOpcode() const { return opcode; }
		InstructionOpcodeImplied getInstruction() const { return instruction; }
		InstructionGroups getGroup() const { return group; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeImplied instruction;
		InstructionGroups group;
		Byte reg;
		Byte srcReg;

	};
}