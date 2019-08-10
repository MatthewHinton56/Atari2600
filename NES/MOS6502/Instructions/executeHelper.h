#pragma once
#include "Binary.h"
#include "InstructionConstants.h"

static int8_t temp = 0;

using namespace mos6502;

inline void groupFunctions
(
	InstructionGroups group,
	Word& PC,
	Memory<PAGE_SIZE, NUM_PAGES>& mem,
	Byte& statusRegister,
	int8_t dataOp,
	Byte& regOp
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
	}
}