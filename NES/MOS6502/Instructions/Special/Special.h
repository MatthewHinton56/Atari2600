#pragma once
#include "../Instruction.h"
#include "SpecialConstants.h"

namespace mos6502
{
	class Special : public Instruction
	{
	public:

		Special
		(
			InstructionSpecial _instruction
		);

		virtual int32_t step
		(
			Word& PC,
			RegisterMap& registerMap, 
			Memory<PAGE_SIZE, NUM_PAGES>& mem
		);

		int32_t getStepCount() const { return stepCount; }
		InstructionSpecial getInstruction() const { return instruction; }
		Byte getLatch() const { return latch; }
		InstructionGroups getGroup() const { return InstructionGroups::spec; }

	private:

		int32_t stepCount;

		InstructionSpecial instruction;
		Byte latch;
		Word interruptVector;
	};
}