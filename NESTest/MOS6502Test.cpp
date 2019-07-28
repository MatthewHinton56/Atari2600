#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class MOS6502Test : public ::testing::Test {
	protected:

		MOS6502Test() :
			mem(),
			mos(mem)
		{}


		void SetUp() override
		{

		}

		Memory<PAGE_SIZE, NUM_PAGES> mem;
		MOS6502 mos;
	};

	TEST_F(MOS6502Test, fetchTest)
	{
		mos.getMemoryAccessor()[0] = 0x08;

		ASSERT_EQ(mos.fetch()->getInstructionType(), Instructions::controlFlowInstructions);

		mos.getMemoryAccessor()[0] = 0x01;

		ASSERT_EQ(mos.fetch()->getInstructionType(), Instructions::standardInstructions);

		mos.getMemoryAccessor()[0] = 0xA0;

		ASSERT_EQ(mos.fetch()->getInstructionType(), Instructions::yxBranchInstructions);

		mos.getMemoryAccessor()[0] = 0xA2;

		ASSERT_EQ(mos.fetch()->getInstructionType(), Instructions::xDecIncInstructions);
	}

}
