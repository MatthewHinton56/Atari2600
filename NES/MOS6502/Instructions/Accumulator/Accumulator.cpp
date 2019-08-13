#pragma once

#include "Accumulator.h"
using namespace mos6502;

static Byte UNUSED = 0;

Accumulator::Accumulator
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeAccumulator>(opcode)),
	type(InstructionToTypeAccumulator[instruction]),
	group(InstructionToGroupAccumulator[instruction])
{
}


int32_t Accumulator::step
(
	Word& PC,
	RegisterMap& registerMap,
	Memory<PAGE_SIZE, NUM_PAGES>& mem
)
{
	stepCount++;
	switch (stepCount)
	{
		case 2:
			mem.readByte(PC);
			return 2;
		
		case 3:
			groupStep
			(
				group,
				PC,
				mem,
				registerMap[SR],
				registerMap[AC],
				registerMap[AC]
			);
			return 1;

	}

	return -1;
}



