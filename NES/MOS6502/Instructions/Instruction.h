#pragma once
#include "InstructionGroup.h"

namespace mos6502
{
	class Instruction
	{
		public:

			virtual int32_t step(Word& PC, RegisterMap& registerMap, Memory<PAGE_SIZE, NUM_PAGES>& mem) = 0;
			virtual InstructionGroups getGroup() const = 0;
	};
}