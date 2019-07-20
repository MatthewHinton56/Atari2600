#pragma once
      
#include "gtest/gtest.h"
#include "pch.h"
#include "MOS6507/Memory.h"

#define COMMA ,

using namespace mos6507;

namespace {

	class MemoryTest : public ::testing::Test {
	protected:

		void SetUp() override 
		{
			page.fill(0);
		}

		Memory<256, 32> mem;
		std::array<uint8_t, 256> page;
	};

	TEST_F(MemoryTest, MemoryConstruction) 
	{
		ASSERT_EQ(mem.getPageSize(), 256);
		ASSERT_EQ(mem.getNumPages(), 32);
		ASSERT_EQ(mem.getAddressSize(), 13);
		ASSERT_EQ(mem.getOffsetAddressSize(), 8);
		ASSERT_EQ(mem.getPageAddressSize(), 5);
		ASSERT_EQ(mem.getTotalBytes(), 8192);
	}

	TEST_F(MemoryTest, MemoryConstructionBadParameters) 
	{
		ASSERT_THROW(Memory<255 COMMA 32> mem, std::invalid_argument);
	}

	TEST_F(MemoryTest, MemoryMask) 
	{
		unsigned int offsetMask = 0xFF;
		unsigned int pageMask = 0x1F00;
		unsigned int addressMask = 0x1FFF;
		ASSERT_EQ(mem.getOffsetMask(), offsetMask);
		ASSERT_EQ(mem.getPageMask(), pageMask);
		ASSERT_EQ(mem.getAddressMask(), addressMask);
	}

	TEST_F(MemoryTest, MemoryReadWrite) 
	{
		mem[0x1CBA] = 0xCA;
		ASSERT_EQ(mem[0x1CBA], 0xCA);
	}

	TEST_F(MemoryTest, MemoryPageReadWrite)
	{
		for (int i = 0; i < 256; i++)
		{
			page[i] = rand() & 0xFF;
		}

		mem.writePage(31, page);

		std::array<uint8_t, 256> actualPage = mem.readPage(31);

		ASSERT_EQ(page.size(), actualPage.size()) << "Vectors x and y are of unequal length";

		for (int i = 0; i < actualPage.size(); ++i) {
			EXPECT_EQ(actualPage[i], page[i]) << "Vectors x and y differ at index " << i;
		}
	}

	TEST_F(MemoryTest, MemoryPageAccessErrors)
	{
		ASSERT_THROW(mem[0xFFDCB], std::invalid_argument);
		ASSERT_THROW(mem.readPage(33), std::invalid_argument);
		ASSERT_THROW(mem.writePage(35, page), std::invalid_argument);
	}

	TEST_F(MemoryTest, MemoryClear)
	{
		for (int i = 0; i < mem.getTotalBytes(); ++i) {
			mem[i] = 0x11;
		}

		mem.clearMemory();

		for (int i = 0; i < mem.getTotalBytes(); ++i) {
			EXPECT_EQ(mem[i], 0x00);
		}
	}
} 
