#pragma once
#include "MOS6502Constants.h"
#include "MemoryAccessor.h"
#include "../Memory.h"
#include "Instructions/Instruction.h"
#include <memory.h>

namespace mos6502
{
	class MOS6502
	{
		public:

			MOS6502
			(
				Memory<PAGE_SIZE, NUM_PAGES>& mem
			);

			virtual ~MOS6502() = default;

			virtual void cycle(bool irq, bool nmi);

			virtual void reset();

			virtual MemoryAccessor& getMemoryAccessor();

			virtual Instruction& getInstruction();

			virtual RegisterMap& getRegisterMap();

			virtual Word getPC();

			virtual unsigned int getCycles();

			virtual bool getNmi();

			virtual void setNmi();

			virtual bool getIrq();

			virtual void setIrq();

			virtual std::unique_ptr<Instruction> fetch();


		private:

			MemoryAccessor memory;
			std::unique_ptr<Instruction> instruction;
			RegisterMap registerMap;
			Word PC;
			
			unsigned int cycles;
			bool nmi;
			bool irq;
			bool res;
	};
}