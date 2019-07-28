#include"Instructions/XDecIncInstructions/XDecIncInstruction.h"
#include"Instructions/StandardInstructions/StandardInstruction.h"
#include"Instructions/ControlFlowInstructions/ControlFlowInstruction.h"
#include"Instructions/YXBranchInstructions/YXBranchInstruction.h"
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

}

void MOS6502::reset()
{

}

MemoryAccessor& MOS6502::getMemoryAccessor()
{
	return memory;
}

Instruction* MOS6502::getInstruction()
{
	return instruction;
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

bool MOS6502::getIrq()
{
	return irq;
}

bool MOS6502::getRes()
{
	return res;
}



Instruction* MOS6502::fetch()
{
	Byte instructionByte = memory[PC];
	Byte lowOrder = memory[PC + 1];
	Byte highOrder = memory[PC + 2];

	uint8_t a = (0xE0 & instructionByte) >> 5;
	uint8_t b = (0x1C & instructionByte) >> 2;
	uint8_t	c = (0x3 & instructionByte);

	uint8_t instructionCA = generateCA(a, c);

	if (instructionCA < 004)
	{
		return new ControlFlowInstruction(a, b, c, PC, lowOrder, highOrder);
	}
	else if (instructionCA < 010)
	{
		return new YXBranchInstruction(a, b, c, PC, lowOrder, highOrder);
	}
	else if (instructionCA < 024)
	{
		return new StandardInstruction(a, b, c, PC, lowOrder, highOrder);
	}
	else
	{
		return new XDecIncInstruction(a, b, c, PC, lowOrder, highOrder);
	}
}

