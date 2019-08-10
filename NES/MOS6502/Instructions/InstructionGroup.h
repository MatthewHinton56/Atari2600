#pragma once
#include "Binary.h"
#include "InstructionConstants.h"

static int8_t temp = 0;

using namespace mos6502;

inline void groupStep
(
	InstructionGroups group,
	Word& PC,
	Memory<PAGE_SIZE, NUM_PAGES>& mem,
	Byte& statusRegister,
	int8_t dataOp,
	Byte& regOp,
	Word address = 0
)
{
	switch (group)
	{
		case InstructionGroups::ld:
			examine
			(
				dataOp,
				statusRegister
			);
			regOp = dataOp;
			break;

		case InstructionGroups::adc:
		case InstructionGroups::sbc:
		case InstructionGroups::cmp:
			regOp = arithmetic
			(
				group,
				regOp,
				dataOp,
				statusRegister
			);
			break;

		case InstructionGroups::ror:
		case InstructionGroups::rol:
		case InstructionGroups::lsr:
		case InstructionGroups::asl:
			regOp = shift
			(
				group,
				dataOp,
				statusRegister
			);
			break;

		case InstructionGroups::nnand:
		case InstructionGroups::eor:
		case InstructionGroups::ora:
			regOp = logic
			(
				group,
				regOp,
				dataOp,
				statusRegister
			);
			break;

		case InstructionGroups::bit:
			(dataOp & 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);
			(dataOp & 0x40) ? setOverflowFlag(statusRegister) : clearOverflowFlag(statusRegister);
			(dataOp & regOp) ? clearZeroFlag(statusRegister) : setZeroFlag(statusRegister);
			break;

		case InstructionGroups::st:
			mem.writeByte(address, regOp);
	}
}