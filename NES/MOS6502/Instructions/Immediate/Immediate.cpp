#pragma once

#include "Immediate.h"
using namespace mos6502;

static Byte UNUSED = 0;

Immediate::Immediate
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeImmediate>(opcode)),
	type(InstructionToTypeImmediate[instruction]),
	group(InstructionToGroupImmediate[instruction]),
	lowAddressByte(0)
{
	switch (instruction)
	{
		default:
			reg = AC;
			break;

		case InstructionOpcodeImmediate::iCpx:
		case InstructionOpcodeImmediate::iLdx:
			reg = X;
			break;

		case InstructionOpcodeImmediate::iCpy:
		case InstructionOpcodeImmediate::iLdy:
			reg = Y;
			break;
	}
}


int32_t Immediate::step
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
			lowAddressByte = mem.readByte(PC);
			PC++;
			return 2;
		
		case 3:
			groupStep
			(
				group,
				PC,
				mem,
				registerMap[SR],
				lowAddressByte,
				registerMap[reg]
			);
			return 1;

	}

	return -1;
}



