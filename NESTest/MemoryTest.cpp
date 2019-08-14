#pragma once
      
#include "pch.h"

#define COMMA ,

using namespace mos6502;

namespace {

	class MemoryTest : public ::testing::Test {
	protected:

		MemoryTest():
		mem(),
		page()
		{}


		void SetUp() override 
		{
			page.fill(0);
		}

		Memory<256, 256> mem;
		std::array<uint8_t, 256> page;
	};

	TEST_F(MemoryTest, MemoryConstruction) 
	{
		ASSERT_EQ(mem.getPageSize(), 256);
		ASSERT_EQ(mem.getNumPages(), 256);
		ASSERT_EQ(mem.getAddressSize(), 16);
		ASSERT_EQ(mem.getOffsetAddressSize(), 8);
		ASSERT_EQ(mem.getPageAddressSize(), 8);
		ASSERT_EQ(mem.getTotalBytes(), 65535);
	}

	TEST_F(MemoryTest, MemoryConstructionBadParameters) 
	{
		ASSERT_THROW(Memory<255 COMMA 32> mem, std::invalid_argument);
	}

	TEST_F(MemoryTest, MemoryMask) 
	{
		unsigned int offsetMask = 0xFF;
		unsigned int pageMask = 0xFF00;
		unsigned int addressMask = 0xFFFF;
		ASSERT_EQ(mem.getOffsetMask(), offsetMask);
		ASSERT_EQ(mem.getPageMask(), pageMask);
		ASSERT_EQ(mem.getAddressMask(), addressMask);
	}

	TEST_F(MemoryTest, MemoryReadWrite) 
	{
		mem.writeByte(0x1CBA, 0xCA);
		ASSERT_EQ(mem.readByte(0x1CBA), 0xCA);
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

		for (size_t i = 0; i < actualPage.size(); ++i) {
			EXPECT_EQ(actualPage[i], page[i]) << "Vectors x and y differ at index " << i;
		}
	}

	TEST_F(MemoryTest, MemoryPageAccessErrors)
	{
		ASSERT_THROW(mem.readPage(257), std::invalid_argument);
		ASSERT_THROW(mem.writePage(358, page), std::invalid_argument);
	}

	static Word num = 0;

	inline void changeNum(Word address, Byte data, bool write)
	{
		num = 5;
	}

	TEST_F(MemoryTest, MemoryListenerTest)
	{
		mem.addMemoryListener(0x44, &changeNum);

		ASSERT_EQ(num, 0);

		mem.writeByte(0x44, 6);

		ASSERT_EQ(num, 5);
	}

	TEST_F(MemoryTest, MemoryMirrorTest)
	{
		mem.writeByte(0x0, 0x55);

		ASSERT_EQ(mem[0x0000], 0x55);
		ASSERT_EQ(mem[0x0800], 0x55);
		ASSERT_EQ(mem[0x1000], 0x55);
		ASSERT_EQ(mem[0x1800], 0x55);

		mem.writeByte(0x07FF, 0xC5);

		ASSERT_EQ(mem[0x07FF], 0xC5);
		ASSERT_EQ(mem[0x0FFF], 0xC5);
		ASSERT_EQ(mem[0x17FF], 0xC5);
		ASSERT_EQ(mem[0x1FFF], 0xC5);

		mem.writeByte(0x2000, 0x12);
		mem.writeByte(0x2001, 0xC3);
		mem.writeByte(0x2002, 0x41);
		mem.writeByte(0x2003, 0x12);
		mem.writeByte(0x2004, 0x91);
		mem.writeByte(0x2005, 0x24);
		mem.writeByte(0x2006, 0x65);
		mem.writeByte(0x2007, 0xF4);

		for (Word address = 0x2000; address < 0x4000; address += ((Word)0x8))
		{
			ASSERT_EQ(mem[address + 0], 0x12);
			ASSERT_EQ(mem[address + 1], 0xC3);
			ASSERT_EQ(mem[address + 2], 0x41);
			ASSERT_EQ(mem[address + 3], 0x12);
			ASSERT_EQ(mem[address + 4], 0x91);
			ASSERT_EQ(mem[address + 5], 0x24);
			ASSERT_EQ(mem[address + 6], 0x65);
			ASSERT_EQ(mem[address + 7], 0xF4);
		}

	}
} 
