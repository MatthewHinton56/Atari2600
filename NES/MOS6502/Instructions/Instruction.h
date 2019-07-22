#pragma once
#include "../MemoryAccessor.h"
#include "../mos6502Constants.h"

namespace mos6502
{
	class Instruction
	{
	public:

		virtual void decode
		(
			RegisterMap& registerMap,
			MemoryAccessor& memory
		) = 0;

		virtual void execute(RegisterMap& registerMap) = 0;

		virtual void writeBack(RegisterMap& registerMap, MemoryAccessor& memory) = 0;

		virtual Word pc() = 0;
	};
}