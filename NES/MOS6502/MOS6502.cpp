#include"Instructions/XDecIncInstructions/XDecIncInstruction.h"
#include"Instructions/StandardInstructions/StandardInstruction.h"
#include"Instructions/ControlFlowInstructions/ControlFlowInstruction.h"
#include"Instructions/YXBranchInstructions/YXBranchInstruction.h"
#include "Instructions/InstructionConstants.h"
#include "MOS6502.h"

using namespace mos6502;

void MOS6502::cycle(bool irq, bool nmi)
{
}

void MOS6502::reset()
{

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

