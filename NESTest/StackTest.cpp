
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class StackTest : public ::testing::Test {
	protected:

		StackTest() :
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

	TEST_F(StackTest, stackBrk)
	{
		PC = 0x3333;
		registerMap[SP] = 0xFF;
		registerMap[SR] = 0xC3;
		mem.writeByte(IRQ_VECTOR, 0x11);
		mem.writeByte(IRQ_VECTOR + 1, 0x12);

		Stack instr(0x00);
		PC++;
		ASSERT_EQ(instr.getOpcode(), 0x00);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeStack::iBrk);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brk);
		ASSERT_EQ(PC, 0x3334);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0x3335);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0x33);
		ASSERT_EQ(registerMap[SP], 0xFE);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0x35);
		ASSERT_EQ(registerMap[SP], 0xFD);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0xD3);
		ASSERT_EQ(registerMap[SP], 0xFC);
		ASSERT_EQ(registerMap[SR], 0xC7);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getLatch(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(PC, 0x1211);
	}
}
