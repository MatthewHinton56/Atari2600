#pragma once
#include "../Instruction.h"
#include "AbsoluteConstant.h"

namespace mos6502
{
	class Absolute
	{
	public:

		Absolute
		(
			Byte opcode
		);

		virtual int32_t step
		(
			Word& PC,
			RegisterMap& registerMap, 
			Memory<PAGE_SIZE, NUM_PAGES>& mem
		);

	private:

		int step_count;

		Byte opcode;
		InstructionOpcodeAbsolute instruction;
		InstructionTypeAbsolute type;
		InstructionGroups group;
		Byte lowAddressByte;
		Byte highAddressByte;
		Word address;
		Byte data;
		Byte reg;
	};
}