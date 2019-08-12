
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class RelativeTest : public ::testing::Test {
	protected:

		RelativeTest() :
			PC(),
			mem(),
			registerMap()
		{}


		void SetUp() override
		{
			PC = 0x10;
			registerMap[SR] = 0xFF;
		}

		Word PC;
		Memory<PAGE_SIZE, NUM_PAGES> mem;
		RegisterMap registerMap;
	};

	TEST_F(RelativeTest, relBpl)
	{
		mem.writeByte(0x11, 0xFF);
		Relative instr(0x10);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x10);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brn);
		ASSERT_EQ(PC, 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0x12);
	}

}
