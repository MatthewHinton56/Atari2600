#pragma once
#include "../Instruction.h"
#include "SpecialConstants.h"

namespace mos6502
{
	class Special
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

	private:

		int32_t stepCount;

		InstructionSpecial instruction;
		Byte latch;
		Word interruptVector;
	};
}