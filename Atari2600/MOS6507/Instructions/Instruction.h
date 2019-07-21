#pragma once
#include "../MemoryAccessor.h"
#include "../MOS6507Constants.h"

namespace mos6507
{
	class Instruction
	{
	public:

		virtual void decode(RegisterMap& registerMap, MemoryAccessor& memory) = 0;

		virtual void execute() = 0;

		virtual void memory(MemoryAccessor& memory) = 0;

		virtual void writeBack(RegisterMap& registerMap) = 0;

		virtual void pc(Word& PC) = 0;
	};
}