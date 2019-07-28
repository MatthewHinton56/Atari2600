#include"Instructions/XDecIncInstructions/XDecIncInstruction.h"
#include"Instructions/StandardInstructions/StandardInstruction.h"
#include"Instructions/ControlFlowInstructions/ControlFlowInstruction.h"
#include"Instructions/YXBranchInstructions/YXBranchInstruction.h"
#include "Instructions/InstructionConstants.h"
#include "MOS6502.h"

using namespace mos6502;

static StandardInstruction dummy(0, 0, 0, 0, 0, 0);

MOS6502::MOS6502
(
	Memory<PAGE_SIZE, NUM_PAGES>& mem
) :
	memory(mem),
	registerMap(),
	instruction(dummy),
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

Instruction& MOS6502::getInstruction()
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



Instruction& MOS6502::fetch()
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
		ControlFlowInstruction cf  = ControlFlowInstruction(a, b, c, PC, lowOrder, highOrder);
		return cf;
	}
	else if (instructionCA < 010)
	{
		YXBranchInstruction yxb = YXBranchInstruction(a, b, c, PC, lowOrder, highOrder);
		return yxb;
	}
	else if (instructionCA < 024)
	{
		StandardInstruction s = StandardInstruction(a, b, c, PC, lowOrder, highOrder);
		return s;
	}
	else
	{
		XDecIncInstruction xdi = XDecIncInstruction(a, b, c, PC, lowOrder, highOrder);
		return xdi;
	}
}

