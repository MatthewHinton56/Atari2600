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

		mos.setIrq();

		ASSERT_EQ(mos.fetch()->getInstructionType(), Instructions::specialInstructions);

		mos.setNmi();

		ASSERT_EQ(mos.fetch()->getInstructionType(), Instructions::specialInstructions);
	}

	TEST_F(MOS6502Test, ResetTest)
	{
		mos.getMemoryAccessor().writeWord(RESET_VECTOR, 0x5555);
		mem[0x5555] = 0xCA;
		mem[0] = 0xC8;

		mos.getRegisterMap()[SR] = 0x45;
		mos.getRegisterMap()[AC] = 0x54;
		mos.getRegisterMap()[SP] = 0x55;

		mos.cycle(false, false);

		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::yxBranchInstructions);

		mos.reset();
		
		ASSERT_EQ(mos.getRegisterMap()[SP], 0xFF);
		ASSERT_EQ(mos.getRegisterMap()[AC], 0x0);
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x00);

		mos.cycle(false, false);

		ASSERT_EQ(mos.getPC(), 0x5555);

		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::xDecIncInstructions);

		mos.cycle(false, false);

		ASSERT_EQ(mos.getRegisterMap()[X], 0xFF);
		ASSERT_EQ(mos.getPC(), 0x5556);
		ASSERT_EQ(mos.getCycles(), 0);
	}



}
