
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class IndirectTest : public ::testing::Test {
	protected:

		IndirectTest() :
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

	TEST_F(IndirectTest, indJmp)
	{
		Indirect instr(0x6C);
		PC++;
		mem.writeByte(0x1, 0xFF);
		mem.writeByte(0x2, 0x1);
		mem.writeByte(0x1FF, 0x34);
		mem.writeByte(0x100, 0x12);
		mem.writeByte(0x1234, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x6C);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::jmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0xFF);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x1);
		ASSERT_EQ(instr.getPointer(), 0x1FF);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getLatch(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(PC, 0x1234);
	}

}
