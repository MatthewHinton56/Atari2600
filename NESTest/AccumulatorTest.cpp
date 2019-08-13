
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class AccumulatorTest : public ::testing::Test {
	protected:

		AccumulatorTest() :
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

	TEST_F(AccumulatorTest, acAsl)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0xC1;
		Accumulator instr(0x0A);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x0A);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAccumulator::iAsl);
		ASSERT_EQ(instr.getType(), InstructionTypeAccumulator::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::asl);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x82);
		ASSERT_EQ(registerMap[SR], 0x81);
	}

	TEST_F(AccumulatorTest, acRol)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0xC1;
		Accumulator instr(0x2A);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x2A);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAccumulator::iRol);
		ASSERT_EQ(instr.getType(), InstructionTypeAccumulator::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::rol);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x83);
		ASSERT_EQ(registerMap[SR], 0x81);
	}

	TEST_F(AccumulatorTest, acLsr)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0xC1;
		Accumulator instr(0x4A);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x4A);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAccumulator::iLsr);
		ASSERT_EQ(instr.getType(), InstructionTypeAccumulator::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::lsr);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x60);
		ASSERT_EQ(registerMap[SR], 0x01);
	}

	TEST_F(AccumulatorTest, acRor)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0xC1;
		Accumulator instr(0x6A);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x6A);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAccumulator::iRor);
		ASSERT_EQ(instr.getType(), InstructionTypeAccumulator::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ror);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0xE0);
		ASSERT_EQ(registerMap[SR], 0x81);
	}
}
