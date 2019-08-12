#pragma once
#include "../Instruction.h"
#include "RelativeConstants.h"

namespace mos6502
{
	class Relative
	{
	public:

		Relative
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
		InstructionOpcodeRelative getInstruction() const { return instruction; }
		InstructionGroups getGroup() const { return group; }
		int8_t getOffset() const { return offset; }
		bool getTaken() const { return taken; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeRelative instruction;
		InstructionGroups group;
		int8_t offset;

		bool taken;
		bool pageTransition;
	};
}