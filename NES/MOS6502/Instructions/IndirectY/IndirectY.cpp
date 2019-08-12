#pragma once

#include "IndirectY.h"
using namespace mos6502;

static Byte UNUSED = 0;

IndirectY::IndirectY
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeIndirectY>(opcode)),
	type(InstructionToTypeIndirectY[instruction]),
	group(InstructionToGroupIndirectY[instruction]),
	lowAddressByte(0),
	highAddressByte(0),
	address(0),
	data(0),
	reg(AC),
	regIndex(Y),
	pointer(0),
	pageBoundaryCrossed(false)
{
	
}


int32_t IndirectY::step
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
			pointer = mem.readByte(PC);
			PC++;
			return 0;

		case 3:
			lowAddressByte = mem.readByte(pointer);
			return 0;

		case 4:
			highAddressByte = mem.readByte(pointer + 1);
			temp = lowAddressByte + registerMap[regIndex];
			pageBoundaryCrossed = temp < lowAddressByte;
			lowAddressByte = temp;
			address = (highAddressByte << 8) | lowAddressByte;

		case 5:
			data = mem.readByte(address);
			highAddressByte += ((pageBoundaryCrossed) ? 1 : 0);
			address = (highAddressByte << 8) | lowAddressByte;
			type = (type == InstructionTypeIndirectY::read && pageBoundaryCrossed) ?
				InstructionTypeIndirectY::iread :
				type;
			return (type == InstructionTypeIndirectY::read) ? 2 : 0;

		case 6:
			switch (type)
			{
				case InstructionTypeIndirectY::read:
					groupStep
					(
						group,
						PC,
						mem,
						registerMap[SR],
						data,
						registerMap[reg]
					);
					return 1;

				case InstructionTypeIndirectY::rmw:
				case InstructionTypeIndirectY::iread:
					data = mem.readByte(address);
					return (type == InstructionTypeIndirectY::iread) ? 2 : 0;

				case InstructionTypeIndirectY::write:
					mem.writeByte(address, registerMap[reg]);
					return 1;
			}

		case 7:
			if (type == InstructionTypeIndirectY::rmw) mem.writeByte(address, data);
			groupStep
			(
				group,
				PC,
				mem,
				registerMap[SR],
				data,
				registerMap[reg]
			);

			return (type == InstructionTypeIndirectY::rmw) ? 0 : 1;

		case 8:
			mem.writeByte(address, data);
			return 1;
	}

	return -1;
}



