#pragma once
#include "MOS6502Constants.h"
#include "Instructions/Instruction.h"
#include <memory.h>

namespace mos6502
{
	class MOS6502
	{
		public:

			MOS6502
			(
				Memory<PAGE_SIZE, NUM_PAGES>& _mem
			);

			virtual ~MOS6502() = default;

			virtual void cycle();

			Memory<PAGE_SIZE, NUM_PAGES>& getMemory() { return mem;  }

			virtual RegisterMap& getRegisterMap();

			virtual Instruction& getInstruction();

			virtual Word getPC();

			virtual bool getNmi();

			virtual void setNmi();

			virtual bool getIrq();

			virtual void setIrq();

			virtual bool getReset();

			virtual void setReset();

			virtual std::unique_ptr<Instruction> fetch();


		private:

			Memory<PAGE_SIZE, NUM_PAGES>& mem;
			RegisterMap registerMap;
			std::unique_ptr<Instruction> instruction;
			Word PC;

			bool nmi;
			bool irq;
			bool reset;
			bool pipeline;
			bool complete;
	};
}