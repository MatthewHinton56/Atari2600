#pragma once

#include "Special.h"
using namespace mos6502;

static Byte UNUSED = 0;

Special::Special
(
	InstructionSpecial _instruction
)	:
	stepCount(1),
	instruction(_instruction),
	latch(0)
{
	switch (instruction)
	{
		case InstructionSpecial::irq:
			interruptVector = IRQ_VECTOR;
			break;

		case InstructionSpecial::nmi:
			interruptVector = NMI_VECTOR;
			break;

		case InstructionSpecial::reset:
			interruptVector = RESET_VECTOR;
			break;

		default:
			interruptVector = 0;
			break;
	}
}


int32_t Special::step
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
			return 0;
		
		case 3:
			if(instruction != InstructionSpecial::reset)
				mem.writeByte(0x0100 | registerMap[SP], static_cast<Byte>(PC >> 8));
			registerMap[SP]--;
			return 0;

		case 4:
			if (instruction != InstructionSpecial::reset)
				mem.writeByte(0x0100 | registerMap[SP], static_cast<Byte>(PC & 0xFF));
			registerMap[SP]--;
			return 0;

		case 5:
			if (instruction != InstructionSpecial::reset)
				mem.writeByte(0x0100 | registerMap[SP], registerMap[SR] | 0x10);
			registerMap[SP]--;
			return 0;

		case 6:
			latch = mem.readByte(interruptVector);
			setInterruptFlag(registerMap[SR]);
			return 0;

		case 7:
			PC = (mem.readByte(interruptVector + 1) << 8) | latch;
			return 1;
	}

	return -1;
}



