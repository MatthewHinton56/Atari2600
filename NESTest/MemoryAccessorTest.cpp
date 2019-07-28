#pragma once

#include "pch.h"

#define COMMA ,

using namespace mos6502;

namespace {

	class MemoryAccessorTest : public ::testing::Test {
	protected:

		MemoryAccessorTest() :
			mem(),
			memory(mem)
		{}

		void SetUp() override
		{
			memory.getMemory().clearMemory();
		}
		Memory<PAGE_SIZE, NUM_PAGES> mem;
		MemoryAccessor memory;
	};

	TEST_F(MemoryAccessorTest, MemoryConstruction)
	{
		ASSERT_EQ(memory.getMemory().getPageSize(), 256);
		ASSERT_EQ(memory.getMemory().getNumPages(), 256);
		ASSERT_EQ(memory.getMemory().getAddressSize(), 16);
		ASSERT_EQ(memory.getMemory().getOffsetAddressSize(), 8);
		ASSERT_EQ(memory.getMemory().getPageAddressSize(), 8);
		ASSERT_EQ(memory.getMemory().getTotalBytes(), 65536);
	}

	TEST_F(MemoryAccessorTest, MemoryReadWord)
	{
		memory.getMemory()[0xB1] = 0xCD;
		memory.getMemory()[0xB2] = 0xAB;
		ASSERT_EQ(memory.readWord(0xB1), 0xABCD);
	}

	TEST_F(MemoryAccessorTest, MemoryWriteWord)
	{
		memory.writeWord(0xB1, 0xABCD);


		ASSERT_EQ(memory[0xB1], 0xCD);
		ASSERT_EQ(memory[0xB2], 0xAB);
	}

	TEST_F(MemoryAccessorTest, MemoryXIndexIndirect)
	{
		memory.getMemory()[0x00] = 0xCD;
		memory.getMemory()[0x01] = 0xAB;
		ASSERT_EQ(memory.xIndexIndirect(0xFF, 1), 0xABCD);
	}

	TEST_F(MemoryAccessorTest, MemoryYIndexIndirect)
	{
		memory.getMemory()[0x00] = 0xCD;
		memory.getMemory()[0x01] = 0xAB;
		bool crossed;
		ASSERT_EQ(memory.yIndexIndirect(0x00, 1, crossed), 0xABCE);
		ASSERT_EQ(crossed, false);

		ASSERT_EQ(memory.yIndexIndirect(0x00, 0xFF, crossed), 0xACCC);
		ASSERT_EQ(crossed, true);
	}

	TEST_F(MemoryAccessorTest, MemoryIndirect)
	{
		memory.getMemory()[0x1FF] = 0xCD;
		memory.getMemory()[0x200] = 0xAB;
		memory.getMemory()[0x100] = 0xEF;

		ASSERT_EQ(memory.indirect(0x1FF), 0xEFCD);
	}

}
