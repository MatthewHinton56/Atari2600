#pragma once

#include "Relative.h"
using namespace mos6502;

static Byte UNUSED = 0;

Relative::Relative
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeRelative>(opcode)),
	group(InstructionGroups::brn),
	offset(0),
	taken(false),
	pageTransition(false)
{

}

int32_t Relative::step
(
	Word& PC,
	RegisterMap& registerMap,
	Memory<PAGE_SIZE, NUM_PAGES>& mem
)
{
	Byte pcLow;
	stepCount++;
	switch (stepCount)
	{
		case 2:
			offset = mem.readByte(PC);
			PC++;
			switch (instruction)
			{
			case InstructionOpcodeRelative::iBpl:
				taken = !getNegativeFlag(registerMap[SR]);
				break;

			case InstructionOpcodeRelative::iBmi:
				taken = getNegativeFlag(registerMap[SR]);
				break;

			case InstructionOpcodeRelative::iBvc:
				taken = !getOverflowFlag(registerMap[SR]);
				break;

			case InstructionOpcodeRelative::iBvs:
				taken = getOverflowFlag(registerMap[SR]);
				break;

			case InstructionOpcodeRelative::iBcc:
				taken = !(getCarryFlag(registerMap[SR]));
				break;

			case InstructionOpcodeRelative::iBcs:
				taken = getCarryFlag(registerMap[SR]);
				break;

			case InstructionOpcodeRelative::iBne:
				taken = !getZeroFlag(registerMap[SR]);
				break;

			case InstructionOpcodeRelative::iBeq:
				taken = !getZeroFlag(registerMap[SR]);
				break;
			}

			return !taken;

		case 3:
			mem.readByte(PC);
			if (taken)
			{
				pcLow = PC & 0xFF;
				temp = ((int8_t)pcLow) + offset;
				pageTransition = (pcLow > temp && offset > 0) || (pcLow < temp && offset < 0);
				PC = (PC & 0xFF00) | temp;
			}

			return (!pageTransition);

		case 4:
			mem.readByte(PC);
			PC += ((offset < 0) ? -0x100 : 0x100);
			return 1;
			
	}

	return -1;
}



