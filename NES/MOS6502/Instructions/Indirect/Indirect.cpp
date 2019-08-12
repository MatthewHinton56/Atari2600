#pragma once

#include "Indirect.h"
using namespace mos6502;

static Byte UNUSED = 0;

Indirect::Indirect
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	group(InstructionGroups::jmp),
	lowAddressByte(0),
	highAddressByte(0),
	address(0),
	data(0),
	pointer(0),
	latch(0)
{
	
}

int32_t Indirect::step
(
	Word& PC,
	RegisterMap& registerMap,
	Memory<PAGE_SIZE, NUM_PAGES>& mem
)
{
	Byte temp;
	stepCount++;
	switch (stepCount)
	{
		case 2:
			lowAddressByte = mem.readByte(PC);
			PC++;
			return 0;

		case 3:
			highAddressByte = mem.readByte(PC);
			PC++;
			pointer = highAddressByte << 8 | lowAddressByte;
			return 0;

		case 4:
			latch = mem.readByte(pointer);
			return 0;

		case 5:
			lowAddressByte++;
			pointer = highAddressByte << 8 | lowAddressByte;
			PC = (mem.readByte(pointer) << 8) | latch;
			return 1;
	}

	return -1;
}



