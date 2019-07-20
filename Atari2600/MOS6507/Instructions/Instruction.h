#pragma once
#include "../MemoryAccessor.h"
#include "../MOS6507Constants.h"

namespace mos6507
{
	class Instruction
	{
	public:

		virtual void decode(RegisterMap& registerMap, MemoryAccessor& memory);

		virtual void execute();

		virtual void memory(MemoryAccessor& memory);

		virtual void writeBack(RegisterMap& registerMap);

		virtual void pc(Word& PC);

	protected:
		virtual Word decodeSelector(instructionAddressingMode mode, RegisterMap& registerMap);

	};
}