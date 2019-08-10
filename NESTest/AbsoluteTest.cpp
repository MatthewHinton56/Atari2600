
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class AbsoluteTest : public ::testing::Test {
	protected:

		AbsoluteTest() :
			PC(),
			mem(),
			registerMap()
		{}


		void SetUp() override
		{
		}

		Word PC;
		Memory<PAGE_SIZE, NUM_PAGES> mem;
		RegisterMap registerMap;
	};

	TEST_F(AbsoluteTest, absBit)
	{
		Absolute instr(0x2C);

		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x2C);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::bit);
	}
}
