#pragma once

#include "Zeropage.h"
using namespace mos6502;

static Byte UNUSED = 0;

Zeropage::Zeropage
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeZeropage>(opcode)),
	type(InstructionToTypeZeropage[instruction]),
	group(InstructionToGroupZeropage[instruction]),
	lowAddressByte(0),
	highAddressByte(0),
	address(0),
	data(0)
{
	switch (instruction)
	{
		default:
			reg = AC;
			break;

		case InstructionOpcodeZeropage::iStx:
		case InstructionOpcodeZeropage::iLdx:
			reg = X;
			break;

		case InstructionOpcodeZeropage::iSty:
		case InstructionOpcodeZeropage::iLdy:
			reg = Y;
			break;
	}
}


int32_t Zeropage::step
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
			address = 0x0000 | lowAddressByte;
			PC++;
			return 0;

		case 3:
			switch (type)
			{
				case InstructionTypeZeropage::rmw:
				case InstructionTypeZeropage::read:
					data = mem.readByte(address);
					return (type == InstructionTypeZeropage::read) ? 2 : 0;

				case InstructionTypeZeropage::write:
					groupStep
					(
						group,
						PC,
						mem,
						registerMap[SR],
						UNUSED,
						registerMap[reg],
						address
					);
					return 1;
			}

		case 4:
			if (type == InstructionTypeZeropage::rmw) mem.writeByte(address, data);
			groupStep
			(
				group,
				PC,
				mem,
				registerMap[SR],
				data,
				registerMap[reg]
			);

			return (type == InstructionTypeZeropage::rmw) ? 0 : 1;

		case 5:
			mem.writeByte(address, data);
			return 1;
	}
}



