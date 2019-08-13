#pragma once

#include "Stack.h"
using namespace mos6502;

static Byte UNUSED = 0;

Stack::Stack
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeStack>(opcode)),
	type(InstructionToTypeStack[instruction]),
	group(InstructionToGroupStack[instruction]),
	lowAddressByte(0),
	latch(0)
{
	switch (instruction)
	{
		default:
			reg = AC;
			break;

		case InstructionOpcodeStack::iPlp:
		case InstructionOpcodeStack::iPhp:
			reg = SR;
			break;
	}
}


int32_t Stack::step
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
			if(group == InstructionGroups::brk || group == InstructionGroups::jsr)
				PC++;
			return 0;
		
		case 3:
			switch (group)
			{
				case InstructionGroups::brk:
					mem.writeByte(0x0100 | registerMap[SP], static_cast<Byte>(PC >> 8));
					registerMap[SP]--;
					return 0;

				case InstructionGroups::pl:
				case InstructionGroups::rts:
				case InstructionGroups::rti:
					mem.readByte(0x0100 | registerMap[SP]);
					registerMap[SP]++;
					return 0;

				case InstructionGroups::ph:
					mem.writeByte(0x0100 | registerMap[SP], registerMap[reg]);
					registerMap[SP]--;
					return 1;

				case InstructionGroups::jsr:
					mem.readByte(0x0100 | registerMap[SP]);
					return 0;

				default:
					return -1;
			}

		case 4:
			switch (group)
			{
				case InstructionGroups::brk:
					mem.writeByte(0x0100 | registerMap[SP], static_cast<Byte>(PC & 0xFF));
					registerMap[SP]--;
					return 0;

				case InstructionGroups::rti:
					registerMap[SR] = mem.readByte(0x0100 | registerMap[SP]);
					registerMap[SP]++;
					return 0;

				case InstructionGroups::rts:
					latch = mem.readByte(0x0100 | registerMap[SP]);
					registerMap[SP]++;
					return 0;

				case InstructionGroups::pl:
					registerMap[reg] = mem.readByte(0x0100 | registerMap[SP]);
					return 1;

				case InstructionGroups::jsr:
					mem.writeByte(0x0100 | registerMap[SP], static_cast<Byte>(PC >> 8));
					registerMap[SP]--;
					return 0;

				default:
					return -1;
			}

		case 5:
			switch (group)
			{
				case InstructionGroups::brk:
					mem.writeByte(0x0100 | registerMap[SP], registerMap[SR] | 0x10);
					registerMap[SP]--;
					return 0;

				case InstructionGroups::rti:
					latch = mem.readByte(0x0100 | registerMap[SP]);
					registerMap[SP]++;
					return 0;

				case InstructionGroups::rts:
					PC = (mem.readByte(0x0100 | registerMap[SP]) << 8) | latch;
					return 0;

				case InstructionGroups::jsr:
					mem.writeByte(0x0100 | registerMap[SP], static_cast<Byte>(PC & 0xFF));
					registerMap[SP]--;
					return 0;

				default:
					return -1;
			}

		case 6:
			switch (group)
			{
				case InstructionGroups::brk:
					latch = mem.readByte(IRQ_VECTOR);
					return 0;

				case InstructionGroups::rti:
					PC = (mem.readByte(0x0100 | registerMap[SP]) << 8) | latch;
					return 1;

				case InstructionGroups::rts:
					PC++;
					return 1;

				case InstructionGroups::jsr:
					PC = (mem.readByte(PC) << 8) | lowAddressByte;
					return 1;

				default:
					return -1;
			}

		case 7:
			PC = (mem.readByte(IRQ_VECTOR + 1) << 8) | latch;
			return 1;

	}

	return -1;
}



