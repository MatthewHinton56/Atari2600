#pragma once
#include "MOS6502Constants.h";
#include "MemoryAccessor.h"
#include "../Memory.h"
#include "Instructions/Instruction.h"

namespace mos6502
{
	class MOS6502
	{


		private:
			MemoryAccessor memoryAccess;
			Instruction instruction;
			RegisterMap registerMap;
			int cycles;

			bool nmi;
			bool irq;
	};
}