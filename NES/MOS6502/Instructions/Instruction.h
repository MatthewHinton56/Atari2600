#pragma once
#include "../../Memory.h"
#include "../mos6502Constants.h"
#include "InstructionConstants.h"

namespace mos6502
{
	class Instruction
	{
		public:

			virtual int32_t step(Word& PC, RegisterMap& registerMap, Memory<PAGE_SIZE, NUM_PAGES>& mem) = 0;
	};
}