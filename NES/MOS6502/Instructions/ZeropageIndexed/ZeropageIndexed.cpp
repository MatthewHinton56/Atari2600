#pragma once

#include "ZeropageIndexed.h"
using namespace mos6502;

static Byte UNUSED = 0;

ZeropageIndexed::ZeropageIndexed
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeZeropageIndexed>(opcode)),
	type(InstructionToTypeZeropageIndexed[instruction]),
	group(InstructionToGroupZeropageIndexed[instruction]),
	lowAddressByte(0),
	address(0),
	data(0)
{
	switch (instruction)
	{
		default:
			reg = AC;
			regIndex = X;
			break;

		case InstructionOpcodeZeropageIndexed::iStx:
		case InstructionOpcodeZeropageIndexed::iLdx:
			reg = X;
			regIndex = Y;
			break;

		case InstructionOpcodeZeropageIndexed::iSty:
		case InstructionOpcodeZeropageIndexed::iLdy:
			reg = Y;
			regIndex = X;
			break;
	}
}


int32_t ZeropageIndexed::step
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
			address = lowAddressByte;
			PC++;
			return 0;

		case 3:
			mem.readByte(address);
			address = static_cast<Byte>(lowAddressByte + registerMap[regIndex]);
			return 0;

		case 4:
			switch (type)
			{
				case InstructionTypeZeropageIndexed::rmw:
				case InstructionTypeZeropageIndexed::read:
					data = mem.readByte(address);
					return (type == InstructionTypeZeropageIndexed::read) ? 2 : 0;

				case InstructionTypeZeropageIndexed::write:
					mem.writeByte(address, registerMap[reg]);
					return 1;
			}

		case 5:
			if (type == InstructionTypeZeropageIndexed::rmw) mem.writeByte(address, data);
			groupStep
			(
				group,
				PC,
				mem,
				registerMap[SR],
				data,
				registerMap[reg]
			);

			return (type == InstructionTypeZeropageIndexed::rmw) ? 0 : 1;

		case 6:
			mem.writeByte(address, data);
			return 1;
	}

	return -1;
}



