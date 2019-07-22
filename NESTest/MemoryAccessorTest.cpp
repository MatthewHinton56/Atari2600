#pragma once

#include "pch.h"

#define COMMA ,

using namespace mos6502;

namespace {

	class MemoryAccessorTest : public ::testing::Test {
	protected:

		MemoryAccessorTest() :
			memory()
		{}

		void SetUp() override
		{
			memory.getMemory().clearMemory();
		}

		MemoryAccessor memory;
	};

	TEST_F(MemoryAccessorTest, MemoryConstruction)
	{
		ASSERT_EQ(memory.getMemory().getPageSize(), 256);
		ASSERT_EQ(memory.getMemory().getNumPages(), 32);
		ASSERT_EQ(memory.getMemory().getAddressSize(), 13);
		ASSERT_EQ(memory.getMemory().getOffsetAddressSize(), 8);
		ASSERT_EQ(memory.getMemory().getPageAddressSize(), 5);
		ASSERT_EQ(memory.getMemory().getTotalBytes(), 8192);
	}

	TEST_F(MemoryAccessorTest, MemoryReadWord)
	{
		memory.getMemory()[0xB1] = 0xCD;
		memory.getMemory()[0xB2] = 0xAB;
		ASSERT_EQ(memory.readWord(0xB1), 0xABCD);
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

}
