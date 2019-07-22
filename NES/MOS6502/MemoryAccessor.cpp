#include "MemoryAccessor.h"

using namespace mos6502;

MemoryAccessor::MemoryAccessor
(

) :
	memory()
{

}

Word MemoryAccessor::readWord(Word address)
{
	Word maskAddress = address & memory.getAddressMask();
	Word lowOrder = memory[address];
	Word highOrder = memory[address + 1];
	return lowOrder | (highOrder << 8);
}

Word MemoryAccessor::indirect
(
	Word address
)
{
	return readWord(address);
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
