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
		);

		virtual void execute(RegisterMap& registerMap);

		virtual void writeBack(RegisterMap& registerMap, MemoryAccessor& memory);

		virtual Word pc();
	};
}