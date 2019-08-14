#pragma once
#include "FetchConstants.h"
#include "MOS6502.h"
#include <string>

using namespace mos6502;

MOS6502::MOS6502
(
	Memory<PAGE_SIZE, NUM_PAGES>& _mem
) :
	mem(_mem),
	registerMap(),
	instruction(),
	PC(0),
	nmi(false),
	irq(false),
	reset(false),
	pipeline(false),
	complete(true)
{
	registerMap[AC] = 0;
	registerMap[X] = 0;
	registerMap[Y] = 0;
	registerMap[SR] = 0x34;
	registerMap[SP] = 0xFD;
}

void MOS6502::cycle()
{

	if (pipeline)
	{
		pipeline = false;
		int32_t result = instruction->step
		(
			PC,
			registerMap,
			mem
		);
		complete = (result == 1);
	}

	if (complete)
	{
		instruction = fetch();
		complete = false;
	}
	else
	{
		int32_t result = instruction->step
		(
			PC,
			registerMap,
			mem
		);
		complete = (result == 1);
		pipeline = (result == 2);
	}

}

Instruction& mos6502::MOS6502::getInstruction()
{
	return (*instruction);
}

RegisterMap& MOS6502::getRegisterMap()
{
	return registerMap;
}

Word mos6502::MOS6502::getPC()
{
	return PC;
}

bool MOS6502::getNmi()
{
	return nmi;
}

void mos6502::MOS6502::setIrq()
{
	if(!getInterruptFlag(registerMap[SR]))
		irq = true;
}

bool mos6502::MOS6502::getReset()
{
	return reset;
}

void mos6502::MOS6502::setReset()
{
	reset = true;
}

void mos6502::MOS6502::setNmi()
{
	nmi = true;
}

bool MOS6502::getIrq()
{
	return irq;
}

std::unique_ptr<Instruction> MOS6502::fetch()
{
	Byte opcode = mem.readByte(PC);
	if (reset)
	{
		reset = false;
		return std::make_unique<Special>(InstructionSpecial::reset);
	}

	if (nmi)
	{
		nmi = false;
		irq = false;

		return std::make_unique<Special>(InstructionSpecial::nmi);
	}

	if (irq)
	{
		irq = false;

		return std::make_unique<Special>(InstructionSpecial::irq);
	}

	PC++;
	Byte bc = 0x1F & opcode;

	if (opcode == INDIRECT_JMP)
	{
		return std::make_unique<Indirect>(opcode);
	}

	if (bc >= 0xC && bc <= 0xE)
	{
		return std::make_unique<Absolute>(opcode);
	}

	if (bc >= 0x4 && bc <= 0x6)
	{
		return std::make_unique<Zeropage>(opcode);
	}

	if ((bc >= 0x1C && bc <= 0x1E) || bc == 0x19)
	{
		return std::make_unique<AbsoluteIndexed>(opcode);
	}

	if (bc >= 0x14 && bc <= 0x16)
	{
		return std::make_unique<ZeropageIndexed>(opcode);
	}

	if (bc == INDIRECT_Y_BC)
	{
		return std::make_unique<IndirectY>(opcode);
	}

	if (bc == RELATIVE_BC)
	{
		return std::make_unique<Relative>(opcode);
	}

	if (bc == INDIRECT_X_BC)
	{
		return std::make_unique<IndirectX>(opcode);
	}

	if (ACCUMULATOR_INSTRUCTIONS.find(opcode) != ACCUMULATOR_INSTRUCTIONS.end())
	{
		return std::make_unique<Accumulator>(opcode);
	}

	if (IMMEDIATE_INSTRUCTIONS.find(opcode) != IMMEDIATE_INSTRUCTIONS.end())
	{
		return std::make_unique<Immediate>(opcode);
	}

	if (IMPLIED_INSTRUCTIONS.find(opcode) != IMPLIED_INSTRUCTIONS.end())
	{
		return std::make_unique<Implied>(opcode);
	}

	if (STACK_INSTRUCTIONS.find(opcode) != STACK_INSTRUCTIONS.end())
	{
		return std::make_unique<Stack>(opcode);
	}

	return std::make_unique<Stack>(0x00);

}

