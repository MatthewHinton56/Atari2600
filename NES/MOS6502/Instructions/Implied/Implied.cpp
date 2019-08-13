#pragma once

#include "Implied.h"
using namespace mos6502;

static Byte UNUSED = 0;

Implied::Implied
(
	Byte _opcode
)	:
	stepCount(1),
	opcode(_opcode),
	instruction(static_cast<InstructionOpcodeImplied>(opcode)),
	group(InstructionToGroupImplied[instruction]),
	reg(0),
	srcReg(0)
{
	switch (instruction)
	{
		case InstructionOpcodeImplied::iTax:
		case InstructionOpcodeImplied::iDex:
		case InstructionOpcodeImplied::iInx:
		case InstructionOpcodeImplied::iTsx:
			reg = X;
			break;

		case InstructionOpcodeImplied::iTay:
		case InstructionOpcodeImplied::iDey:
		case InstructionOpcodeImplied::iIny:
			reg = Y;
			break;

		case InstructionOpcodeImplied::iTxs:
			reg = SP;
			break;

		default:
			reg = AC;
	}

	switch (instruction)
	{
		case InstructionOpcodeImplied::iTxs:
		case InstructionOpcodeImplied::iTxa:
			srcReg = X;
			break;

		case InstructionOpcodeImplied::iTya:
			srcReg = Y;
			break;

		case InstructionOpcodeImplied::iTax:
		case InstructionOpcodeImplied::iTay:
			srcReg = AC;
			break;

		case InstructionOpcodeImplied::iTsx:
			srcReg = SP;
			break;
	}
}


int32_t Implied::step
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
			return 2;
		
		case 3:
			switch (group)
			{
				case InstructionGroups::clc:
					clearCarryFlag(registerMap[SR]);
					break;

				case InstructionGroups::sec:
					setCarryFlag(registerMap[SR]);
					break;

				case InstructionGroups::cli:
					clearInterruptFlag(registerMap[SR]);
					break;

				case InstructionGroups::sei:
					setInterruptFlag(registerMap[SR]);
					break;

				case InstructionGroups::clv:
					clearOverflowFlag(registerMap[SR]);
					break;

				case InstructionGroups::sed:
					setDecimalFlag(registerMap[SR]);
					break;

				case InstructionGroups::cld:
					clearDecimalFlag(registerMap[SR]);
					break;

				case InstructionGroups::trf:
					transfer
					(
						registerMap[srcReg],
						registerMap[reg],
						registerMap[SR]
					);
					break;

				default:
					groupStep
					(
						group,
						PC,
						mem,
						registerMap[SR],
						registerMap[reg],
						registerMap[reg]
					);
					break;
			}

			return 1;

	}

	return -1;
}



