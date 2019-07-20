#include "MemoryAccessor.h"

using namespace mos6507;

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
	Byte registerY
)
{
	return readWord(address) + registerY;
}

Memory<PAGE_SIZE, NUM_PAGES>& mos6507::MemoryAccessor::getMemory()
{
	return memory;
}
