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

	TEST_F(MOS6502Test, MultiInstructionTest)
	{
		//LDX #0x80
		mem[0] = 0xA2;
		mem[1] = 0x80;

		//LDA #0x3E
		mem[2] = 0xA9;
		mem[3] = 0x3E;

		//STA 0x1111
		mem[4] = 0x8D;
		mem[5] = 0x11;
		mem[6] = 0x11;

		//INC 0x1091 X
		mem[7] = 0xFE;
		mem[8] = 0x91;
		mem[9] = 0x10;

		//LDY 0x1091 X
		mem[10] = 0xBC;
		mem[11] = 0x91;
		mem[12] = 0x10;

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 2);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::xDecIncInstructions);
		mos.cycle(false, false);
		ASSERT_EQ(mos.getRegisterMap()[X], 0x80);
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x80);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 2);

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 2);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::standardInstructions);
		mos.cycle(false, false);
		ASSERT_EQ(mos.getRegisterMap()[AC], 0x3E);
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x00);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 4);

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 4);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::standardInstructions);
		mos.cycle(false, false);
		mos.cycle(false, false);
		mos.cycle(false, false);
		ASSERT_EQ(mem[0x1111], 0x3E);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 7);

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 7);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::xDecIncInstructions);
		mos.cycle(false, false);
		mos.cycle(false, false);
		mos.cycle(false, false);
		mos.cycle(false, false);
		mos.cycle(false, false);
		mos.cycle(false, false);
		ASSERT_EQ(mem[0x1111], 0x3F);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 10);

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 5);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::yxBranchInstructions);
		mos.cycle(false, false);
		mos.cycle(false, false);
		mos.cycle(false, false);
		mos.cycle(false, false);
		ASSERT_EQ(mos.getRegisterMap()[Y], 0x3F);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 13);

	}


	TEST_F(MOS6502Test, BranchInstructionTest)
	{
		//BMI #0x11
		mem[0] = 0x30;
		mem[1] = 0x11;

		//BVC 0x7C
		mem[2] = 0x50;
		mem[3] = 0x7C;

		//SEC
		mem[0x80] = 0x38;

		//BCS 0x7D
		mem[0x81] = 0xB0;
		mem[0x82] = 0x7D;

		mem[0x100] = 0xF8;

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 2);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::controlFlowInstructions);
		mos.cycle(false, false);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 2);

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 3);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::controlFlowInstructions);
		mos.cycle(false, false);
		mos.cycle(false, false);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 0x80);

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 2);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::controlFlowInstructions);
		mos.cycle(false, false);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 0x81);
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x01);

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 4);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::yxBranchInstructions);
		mos.cycle(false, false);
		mos.cycle(false, false);
		mos.cycle(false, false);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 0x100);

		mos.cycle(false, false);
		ASSERT_EQ(mos.getInstruction().getCycles(), 2);
		ASSERT_EQ(mos.getInstruction().getInstructionType(), Instructions::yxBranchInstructions);
		mos.cycle(false, false);
		ASSERT_EQ(mos.getCycles(), 0);
		ASSERT_EQ(mos.getPC(), 0x101);
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x09);
	}
}
