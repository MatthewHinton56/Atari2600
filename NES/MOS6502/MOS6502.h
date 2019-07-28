#pragma once
#include "MOS6502Constants.h"
#include "MemoryAccessor.h"
#include "../Memory.h"
#include "Instructions/Instruction.h"

namespace mos6502
{
	class MOS6502
	{
		virtual void cycle(bool irq, bool nmi);


		virtual void reset();


		private:

			virtual  Instruction& fetch();

			MemoryAccessor memory;
			Instruction& instruction;
			RegisterMap registerMap;
			Word PC;
			
			unsigned int cycles;
			bool nmi;
			bool irq;
	};
}