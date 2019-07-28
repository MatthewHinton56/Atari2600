#include "MemoryAccessor.h"

using namespace mos6502;

MemoryAccessor::MemoryAccessor
(
	Memory<PAGE_SIZE, NUM_PAGES>& memory
) :
	memory(memory)
{

}

Word MemoryAccessor::readWord(Word address)
{
	Word maskAddress = address & memory.getAddressMask();
	Word lowOrder = memory[address];
	Word highOrder = memory[address + 1];
	return lowOrder | (highOrder << 8);
}

Word MemoryAccessor::readWordNoCarry(Word address)
{
	Word maskAddress = address & memory.getAddressMask();
	Word lowOrder = memory[address];

	Byte highOrderNo = ((Byte)address & 0x00FF) + 1;

	Word highOrderAddress = (0xFF00 & address) | highOrderNo;

	Word highOrder = memory[highOrderAddress];
	return lowOrder | (highOrder << 8);
}


void mos6502::MemoryAccessor::writeWord
(
	Word address, 
	Word data
)
{
	Byte lowOrder = data & 0x00FF;
	Byte highOrder = ((data & 0xFF00) >> 8);
	memory[address] = lowOrder;
	memory[address + 1] = highOrder;
}

Word MemoryAccessor::indirect
(
	Word address
)
{
	return readWordNoCarry(address);
}

Word MemoryAccessor::xIndexIndirect
(
	Byte address, 
	Byte registerX
)
{
	Byte newAddress = address + registerX;
	return readWord(newAddress);
}

Word MemoryAccessor::yIndexIndirect
(
	Byte address, 
	Byte registerY,
	bool& crossedPage
)
{
	Word newAddress = readWord(address);
	Word page = memory.getPageMask() & newAddress;

	newAddress += registerY;
	Word newPage = memory.getPageMask() & newAddress;
	crossedPage = (page != newPage);
	return newAddress;
}

Memory<PAGE_SIZE, NUM_PAGES>& MemoryAccessor::getMemory()
{
	return memory;
}
