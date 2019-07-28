#include "Instructions/XDecIncInstructions/XDecIncInstruction.h"
#include "Instructions/StandardInstructions/StandardInstruction.h"
#include "Instructions/ControlFlowInstructions/ControlFlowInstruction.h"
#include "Instructions/YXBranchInstructions/YXBranchInstruction.h"
#include "Instructions/SpecialInstructions/SpecialInstruction.h"
#include "Instructions/InstructionConstants.h"
#include "MOS6502.h"

using namespace mos6502;

MOS6502::MOS6502
(
	Memory<PAGE_SIZE, NUM_PAGES>& mem
) :
	memory(mem),
	registerMap(),
	instruction(),
	cycles(0),
	PC(0),
	nmi(false),
	irq(false),
	res(false)
{
	registerMap[AC] = 0;
	registerMap[X] = 0;
	registerMap[Y] = 0;
	registerMap[SR] = 0;
	registerMap[SP] = 0;
}

void MOS6502::cycle(bool irq, bool nmi)
{
	this->irq = (this->irq) ? this->irq : irq;
	this->nmi = (this->nmi) ? this->nmi : nmi;

	if (cycles == 0)
	{
		instruction = fetch();
		instruction->decode(registerMap, memory);
		instruction->execute(registerMap);
		cycles++;
		return;
	}

	cycles++;

	if (cycles < instruction->getCycles())
	{
		return;
	}

	if (cycles == instruction->getCycles())
	{
		instruction->writeBack(registerMap, memory);
		PC = instruction->pc();
		instruction.reset();
		cycles = 0;
	}
}

void MOS6502::reset()
{
	instruction.reset();
	memory.getMemory().clearMemory();
	registerMap[AC] = 0;
	registerMap[X] = 0;
	registerMap[Y] = 0;
	registerMap[SR] = 0;
	registerMap[SP] = 0;
	cycles = 0;
	res = true;
	irq = false;
	nmi = false;
}

MemoryAccessor& MOS6502::getMemoryAccessor()
{
	return memory;
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

unsigned int MOS6502::getCycles()
{
	return cycles;
}

bool MOS6502::getNmi()
{
	return nmi;
}

void mos6502::MOS6502::setIrq()
{
	irq = true;
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
	if (res)
	{
		PC = memory.readWord(RESET_VECTOR);
		res = false;
	}
	else if (nmi)
	{
		nmi = false;
		return std::make_unique<SpecialInstruction>(SpecialInstructions::iBrkNmi, PC);
	}
	else if (irq && !getInterruptFlag(registerMap[SR]))
	{
		irq = false;
		return std::make_unique<SpecialInstruction>(SpecialInstructions::iBrkIrq, PC);
	}

	Byte instructionByte = memory[PC];
	Byte lowOrder = memory[PC + 1];
	Byte highOrder = memory[PC + 2];

	uint8_t a = (0xE0 & instructionByte) >> 5;
	uint8_t b = (0x1C & instructionByte) >> 2;
	uint8_t	c = (0x3 & instructionByte);

	uint8_t instructionCA = generateCA(a, c);

	if (instructionCA < 004)
	{
		return std::make_unique <ControlFlowInstruction>(a, b, c, PC, lowOrder, highOrder);
	}
	else if (instructionCA < 010)
	{
		return std::make_unique <YXBranchInstruction>(a, b, c, PC, lowOrder, highOrder);
	}
	else if (instructionCA < 024)
	{
		return std::make_unique <StandardInstruction>(a, b, c, PC, lowOrder, highOrder);
	}
	else
	{
		return std::make_unique <XDecIncInstruction>(a, b, c, PC, lowOrder, highOrder);
	}
}

