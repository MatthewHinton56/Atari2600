#pragma once

#include "AbsoluteIndexed.h"
using namespace mos6502;

static Byte UNUSED = 0;

AbsoluteIndexed::AbsoluteIndexed
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeAbsoluteIndexed>(opcode)),
	type(InstructionToTypeAbsoluteIndexed[instruction]),
	group(InstructionToGroupAbsoluteIndexed[instruction]),
	lowAddressByte(0),
	highAddressByte(0),
	address(0),
	data(0)
{
	switch (instruction)
	{
		default:
			reg = AC;
			regIndex = X;
			break;

		case InstructionOpcodeAbsoluteIndexed::iLdx:
			reg = X;
			regIndex = Y;
			break;

		case InstructionOpcodeAbsoluteIndexed::iOraY:
		case InstructionOpcodeAbsoluteIndexed::iAndY:
		case InstructionOpcodeAbsoluteIndexed::iEorY:
		case InstructionOpcodeAbsoluteIndexed::iAdcY:
		case InstructionOpcodeAbsoluteIndexed::iStaY:
		case InstructionOpcodeAbsoluteIndexed::iLdaY:
		case InstructionOpcodeAbsoluteIndexed::iCmpY:
		case InstructionOpcodeAbsoluteIndexed::iSbcY:
			reg = AC;
			regIndex = Y;
			break;
	}
}


int32_t AbsoluteIndexed::step
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
			lowAddressByte = mem.readByte(PC);
			PC++;
			return 0;

		case 3:
			highAddressByte = mem.readByte(PC);
			PC++;
			temp = lowAddressByte + registerMap[regIndex];
			pageBoundaryCrossed = temp < lowAddressByte;
			lowAddressByte = temp;
			address = (highAddressByte << 8) | lowAddressByte;

			return 0;

		case 4:
			data = mem.readByte(address);
			highAddressByte += ((pageBoundaryCrossed) ? 1 : 0);
			address = (highAddressByte << 8) | lowAddressByte;
			type = (type == InstructionTypeAbsoluteIndexed::read && pageBoundaryCrossed) ?
				InstructionTypeAbsoluteIndexed::iread :
				type;
			return (type == InstructionTypeAbsoluteIndexed::read) ? 2 : 0;

		case 5:
			switch (type)
			{
				case InstructionTypeAbsoluteIndexed::read:
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

				case InstructionTypeAbsoluteIndexed::rmw:
				case InstructionTypeAbsoluteIndexed::iread:
					data = mem.readByte(address);
					return (type == InstructionTypeAbsoluteIndexed::iread) ? 2 : 0;

				case InstructionTypeAbsoluteIndexed::write:
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

		case 6:
			if (type == InstructionTypeAbsoluteIndexed::rmw) mem.writeByte(address, data);
			groupStep
			(
				group,
				PC,
				mem,
				registerMap[SR],
				data,
				registerMap[reg]
			);

			return (type == InstructionTypeAbsoluteIndexed::rmw) ? 0 : 1;

		case 7:
			mem.writeByte(address, data);
			return 1;
	}

	return -1;
}



