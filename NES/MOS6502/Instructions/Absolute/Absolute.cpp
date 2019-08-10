#include "Absolute.h"
#include "../Binary.h"
#include "../InstructionGroup.h"
using namespace mos6502;


Absolute::Absolute
(
	Byte _opcode
)	:
	step_count(2),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeAbsolute>(opcode)),
	type(InstructionToTypeAbsolute[instruction]),
	group(InstructionGroups(instruction)),
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

		case InstructionOpcodeAbsolute::iStx:
		case InstructionOpcodeAbsolute::iLdx:
			reg = X;
			break;

		case InstructionOpcodeAbsolute::iSty:
		case InstructionOpcodeAbsolute::iLdy:
			reg = Y;
			break;
	}
}


int32_t Absolute::step
(
	Word& PC,
	RegisterMap& registerMap,
	Memory<PAGE_SIZE, NUM_PAGES>& mem
)
{
	int step_temp = step_count;
	step_count++;
	switch (step_temp)
	{
		case 2:
			lowAddressByte = mem.readByte(PC);
			PC++;
			return 0;

		case 3:
			highAddressByte = mem.readByte(PC);
			PC++;
			address = (highAddressByte << 8) | lowAddressByte;
			if (type == InstructionTypeAbsolute::jmp)
			{
				PC = address;
				return 1;
			}

			return 0;

		case 4:
			switch (type)
			{
				case InstructionTypeAbsolute::rmw:
				case InstructionTypeAbsolute::read:
					data = mem.readByte(address);
					return (type == InstructionTypeAbsolute::read) ? 2 : 0;

				case InstructionTypeAbsolute::write:
					groupStep
					(
						group,
						PC,
						mem,
						registerMap[SR],
						0,
						registerMap[reg],
						address
					);
					return 1;
			}

		case 5:
		{
			Byte& reference = (type == InstructionTypeAbsolute::rmw) ? data : registerMap[reg];
			int32_t ret = (type == InstructionTypeAbsolute::rmw) ? 0 : 1;
			if (type == InstructionTypeAbsolute::rmw) mem.writeByte(address, data);
			groupStep
			(
				group,
				PC,
				mem,
				registerMap[SR],
				data,
				reference
			);

			return ret;
		}
		case 6:
			mem.writeByte(address, data);
			return 1;
	}
}

