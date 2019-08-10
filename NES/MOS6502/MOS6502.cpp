#include "Instructions/InstructionConstants.h"
#include "MOS6502.h"

using namespace mos6502;

MOS6502::MOS6502
(
	Memory<PAGE_SIZE, NUM_PAGES>& mem
) :
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
	registerMap[SR] = 0x04;
	registerMap[SP] = 0xFF;
}

void MOS6502::cycle(bool irq, bool nmi)
{

}

void MOS6502::reset()
{
	instruction.reset();
	registerMap[AC] = 0;
	registerMap[X] = 0;
	registerMap[Y] = 0;
	registerMap[SR] = 0;
	registerMap[SP] = 0xFF;
	cycles = 0;
	res = true;
	irq = false;
	nmi = false;
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

}

