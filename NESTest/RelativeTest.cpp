
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
		ASSERT_EQ(instr.getTaken(), false);
		ASSERT_EQ(instr.getOffset(), -1);

	}

	TEST_F(RelativeTest, relBmi)
	{
		mem.writeByte(0x11, 0x10);
		Relative instr(0x30);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x30);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brn);
		ASSERT_EQ(PC, 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0x12);
		ASSERT_EQ(instr.getTaken(), true);
		ASSERT_EQ(instr.getOffset(), 16);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(PC, 0x22);
	}

	TEST_F(RelativeTest, relBvc)
	{
		mem.writeByte(0x11, 0xFF);
		Relative instr(0x50);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x50);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brn);
		ASSERT_EQ(PC, 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0x12);
		ASSERT_EQ(instr.getTaken(), false);
		ASSERT_EQ(instr.getOffset(), -1);

	}

	TEST_F(RelativeTest, relBvs)
	{
		mem.writeByte(0x11, 0xF0);
		Relative instr(0x70);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x70);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brn);
		ASSERT_EQ(PC, 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0x12);
		ASSERT_EQ(instr.getTaken(), true);
		ASSERT_EQ(instr.getOffset(), -16);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(PC, 0x2);
	}

	TEST_F(RelativeTest, relBcc)
	{
		mem.writeByte(0x11, 0xFF);
		Relative instr(0x90);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x90);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brn);
		ASSERT_EQ(PC, 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0x12);
		ASSERT_EQ(instr.getTaken(), false);
		ASSERT_EQ(instr.getOffset(), -1);
	}

	TEST_F(RelativeTest, relBcs)
	{
		PC = 0xF0;
		mem.writeByte(0xF1, 0x10);
		Relative instr(0xB0);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xB0);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brn);
		ASSERT_EQ(PC, 0xF1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0xF2);
		ASSERT_EQ(instr.getTaken(), true);
		ASSERT_EQ(instr.getOffset(), 16);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(PC, 0x02);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(PC, 0x102);
	}

	TEST_F(RelativeTest, relBne)
	{
		mem.writeByte(0x11, 0xFF);
		Relative instr(0xD0);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xD0);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brn);
		ASSERT_EQ(PC, 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0x12);
		ASSERT_EQ(instr.getTaken(), false);
		ASSERT_EQ(instr.getOffset(), -1);
	}

	TEST_F(RelativeTest, relBeq)
	{

		mem.writeByte(0x11, 0xE0);
		Relative instr(0xB0);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xB0);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brn);
		ASSERT_EQ(PC, 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0x12);
		ASSERT_EQ(instr.getTaken(), true);
		ASSERT_EQ(instr.getOffset(), -32);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(PC, 0xF2);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(PC, 0xFFF2);
	}
}
