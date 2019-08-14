
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
	
	TEST_F(MOS6502Test, ResetTest)
	{
		mos.getMemory()[RESET_VECTOR] = 0x55;
		mos.getMemory()[RESET_VECTOR + 1] = 0x55;
			
		mem[0x5555] = 0xCA;
		mem[0] = 0xC8;

		mos.getRegisterMap()[SR] = 0x41;
		mos.getRegisterMap()[AC] = 0x54;
		mos.getRegisterMap()[X] = 0xFD;
		mos.getRegisterMap()[Y] = 0x3C;
		mos.getRegisterMap()[SP] = 0x55;

		mos.setReset();

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();

		ASSERT_EQ(mos.getPC(), 0x5555);

		ASSERT_EQ(mos.getRegisterMap()[SP], 0x52);
		ASSERT_EQ(mos.getRegisterMap()[AC], 0x54);
		ASSERT_EQ(mos.getRegisterMap()[X], 0xFD);
		ASSERT_EQ(mos.getRegisterMap()[Y], 0x3C);
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x45);
		mos.cycle();

		ASSERT_EQ(mos.getPC(), 0x5556);
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

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 2);

		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[X], 0x80);
		ASSERT_EQ(mos.getRegisterMap()[SR], 0xB4);

		mos.cycle();
		ASSERT_EQ(mos.getPC(), 4);

		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[AC], 0x3E);
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x34);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mem[0x1111], 0x3E);
		ASSERT_EQ(mos.getPC(), 7);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mem[0x1111], 0x3F);
		ASSERT_EQ(mos.getPC(), 10);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 13);

		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[Y], 0x3F);
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

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 2);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x80);

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x81);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x35);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x100);

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x101);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x3D);

	}
	
	TEST_F(MOS6502Test, NmiBrkTest)
	{
		mem[0x1234] = 0x55;

		mos.getRegisterMap()[AC] = 0xAA;

		//ASL
		mem[0] = 0x0E;
		mem[1] = 0x34;
		mem[2] = 0x12;

		mem[NMI_VECTOR] = 0x55;
		mem[NMI_VECTOR + 1] = 0x55;

		mem[0x5555] = 0x4A;
		mem[0x5556] = 0x40;

		mem[3] = 0x38;

		mos.cycle();
		mos.setNmi();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 3);
		ASSERT_EQ(mem[0x1234], 0xAA);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x5555);

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x5556);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[AC], 0x55);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x3);
	}

	TEST_F(MOS6502Test, IrqBrkTest)
	{
		mem[0x1234] = 0x55;
		mos.getRegisterMap()[SR] = 0x0;
		mos.getRegisterMap()[AC] = 0xAA;

		//ASL
		mem[0] = 0x0E;
		mem[1] = 0x34;
		mem[2] = 0x12;

		mem[IRQ_VECTOR] = 0x55;
		mem[IRQ_VECTOR + 1] = 0x55;

		mem[0x5555] = 0x4A;
		mem[0x5556] = 0x40;

		mem[3] = 0x38;

		mos.cycle();
		mos.setIrq();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 3);
		ASSERT_EQ(mem[0x1234], 0xAA);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x5555);

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x5556);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[AC], 0x55);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x3);
	}
	
	TEST_F(MOS6502Test, IrqMaskTest)
	{
		mem[0] = 0x38;
		mem[1] = 0xF8;

		mos.cycle();

		mos.cycle();
		ASSERT_EQ(mos.getPC(), 1);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x35);

		mos.cycle();
		ASSERT_EQ(mos.getPC(), 2);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[SR], 0x3D);
	}

	
	TEST_F(MOS6502Test, SubroutineTest)
	{
		//OR FF
		mem[0] = 0x09;
		mem[1] = 0xFF;

		//JSR 1000
		mem[2] = 0x20;
		mem[3] = 0x00;
		mem[4] = 0x10;

		//AND 0xOF
		mem[0x1000] = 0x29;
		mem[0x1001] = 0x0F;

		mem[0x1002] = 0x60;

		mem[5] = 0x49;
		mem[6] = 0x05;

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 2);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[AC], 0xFF);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mem[0x1FD - 1] = 0x04;
		mem[0x1FD - 0] = 0x00;
		ASSERT_EQ(mos.getRegisterMap()[SP], 0xFD - 2);
		ASSERT_EQ(mos.getPC(), 0x1000);

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x1002);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[AC], 0x0F);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[SP], 0xFD);
		ASSERT_EQ(mos.getPC(), 0x5);

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x7);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[AC], 0x0A);
	}
	
	TEST_F(MOS6502Test, BrkTest)
	{
		mem[0x1234] = 0x55;
		mos.getRegisterMap()[SR] = 0x0;
		mos.getRegisterMap()[AC] = 0xAA;

		//ASL
		mem[0] = 0x0E;
		mem[1] = 0x34;
		mem[2] = 0x12;
		mem[3] = 0x00;
		mem[IRQ_VECTOR] = 0x55;
		mem[IRQ_VECTOR + 1] = 0x55;

		mem[0x5555] = 0x4A;
		mem[0x5556] = 0x40;

		mem[5] = 0x38;

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 3);
		ASSERT_EQ(mem[0x1234], 0xAA);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x5555);

		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x5556);
		mos.cycle();
		ASSERT_EQ(mos.getRegisterMap()[AC], 0x55);

		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		mos.cycle();
		ASSERT_EQ(mos.getPC(), 0x5);
	}
	
}
