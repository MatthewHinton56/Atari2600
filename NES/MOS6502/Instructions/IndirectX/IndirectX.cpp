#pragma once

#include "IndirectX.h"
using namespace mos6502;

static Byte UNUSED = 0;

IndirectX::IndirectX
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeIndirectX>(opcode)),
	type(InstructionToTypeIndirectX[instruction]),
	group(InstructionToGroupIndirectX[instruction]),
	lowAddressByte(0),
	highAddressByte(0),
	address(0),
	data(0),
	reg(AC),
	regIndex(X),
	pointer(0)
{
	
}


int32_t IndirectX::step
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
			mem.readByte(pointer);
			pointer += registerMap[regIndex];
			return 0;

		case 4:
			lowAddressByte = mem.readByte(pointer);
			return 0;

		case 5:
			highAddressByte = mem.readByte(pointer + 1);
			address = (highAddressByte << 8) | lowAddressByte;
			return 0;

		case 6:
			switch (type)
			{

				case InstructionTypeIndirectX::rmw:
				case InstructionTypeIndirectX::read:
					data = mem.readByte(address);
					return (type == InstructionTypeIndirectX::read) ? 2 : 0;

				case InstructionTypeIndirectX::write:
					mem.writeByte(address, registerMap[reg]);
					return 1;
			}

		case 7:
			if (type == InstructionTypeIndirectX::rmw) mem.writeByte(address, data);
			groupStep
			(
				group,
				PC,
				mem,
				registerMap[SR],
				data,
				registerMap[reg]
			);

			return (type == InstructionTypeIndirectX::rmw) ? 0 : 1;

		case 8:
			mem.writeByte(address, data);
			return 1;
	}

	return -1;
}



