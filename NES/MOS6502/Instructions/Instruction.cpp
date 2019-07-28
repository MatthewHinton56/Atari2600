#include "Instruction.h"
#include "../MOS6502Constants.h"

using namespace mos6502;

void mos6502::Instruction::decode(RegisterMap& registerMap, MemoryAccessor& memory)
{
}

void mos6502::Instruction::execute(RegisterMap& registerMap)
{
}

void mos6502::Instruction::writeBack(RegisterMap& registerMap, MemoryAccessor& memory)
{
}

Word Instruction::pc()
{
	return Word();
}
