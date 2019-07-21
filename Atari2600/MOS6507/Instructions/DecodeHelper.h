#pragma once
#include "../MOS6507Constants.h"
#include "../MemoryAccessor.h"

namespace mos6507
{
	static bool crossed = false;
	inline Word absolute
	(
		MemoryAccessor& memory,
		Byte lowOrderOperand,
		Byte highOrderOperand,
		Byte registerVal = 0,
		bool& crossedPage = crossed
	)
	{
		Word page;
		Word newPage;
		Word address;
		address = highOrderOperand << 8 | lowOrderOperand;
		page = memory.getMemory().getPageMask() & address;

		address += registerVal;
		newPage = memory.getMemory().getPageMask() & address;
		crossedPage = (page != newPage);
		std::cout << crossedPage << std::endl;
		return address;
	}

	inline Byte zeroPage
	(
		Byte lowOrderOperand,
		Byte registerVal = 0
	)
	{
		Byte address = (registerVal + lowOrderOperand);
		return address;
	}

	inline Word xIndirect
	(
		MemoryAccessor& memory,
		Byte lowOrderOperand,
		Byte registerVal = 0
	)
	{
		return memory.xIndexIndirect(lowOrderOperand, registerVal);
	}

	inline Word yIndirect
	(
		MemoryAccessor& memory,
		Byte lowOrderOperand,
		Byte registerVal = 0,
		bool& crossedPage = crossed
	)
	{
		return memory.yIndexIndirect(lowOrderOperand, registerVal, crossedPage);
	}
}
