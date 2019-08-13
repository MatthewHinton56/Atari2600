
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class ImpliedTest : public ::testing::Test {
	protected:

		ImpliedTest() :
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

	TEST_F(ImpliedTest, implDey)
	{
		registerMap[Y] = 0x1;
		registerMap[SR] = 0x0;
		Implied instr(0x88);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x88);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iDey);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::dec);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[Y], 0x0);
		ASSERT_EQ(registerMap[SR], 0x2);
	}

	TEST_F(ImpliedTest, implTay)
	{
		registerMap[AC] = 0xBC;
		registerMap[Y] = 0x32;
		registerMap[SR] = 0x0;
		Implied instr(0xA8);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xA8);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iTay);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::trf);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[Y], 0xBC);
		ASSERT_EQ(registerMap[SR], 0x80);
	}

	TEST_F(ImpliedTest, implIny)
	{
		registerMap[Y] = 0x1;
		registerMap[SR] = 0x0;
		Implied instr(0xC8);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xC8);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iIny);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::inc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[Y], 0x2);
		ASSERT_EQ(registerMap[SR], 0x0);
	}

	TEST_F(ImpliedTest, implInx)
	{
		registerMap[X] = 0x1;
		registerMap[SR] = 0x0;
		Implied instr(0xE8);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xE8);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iInx);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::inc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[X], 0x2);
		ASSERT_EQ(registerMap[SR], 0x0);
	}

	TEST_F(ImpliedTest, implTxa)
	{
		registerMap[AC] = 0xBC;
		registerMap[X] = 0x32;
		registerMap[SR] = 0x0;
		Implied instr(0x8A);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x8A);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iTxa);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::trf);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x32);
		ASSERT_EQ(registerMap[SR], 0x00);
	}

	TEST_F(ImpliedTest, implTax)
	{
		registerMap[AC] = 0xBC;
		registerMap[X] = 0x32;
		registerMap[SR] = 0x0;
		Implied instr(0xAA);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xAA);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iTax);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::trf);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[X], 0xBC);
		ASSERT_EQ(registerMap[SR], 0x80);
	}

	TEST_F(ImpliedTest, implDex)
	{
		registerMap[X] = 0x1;
		registerMap[SR] = 0x0;
		Implied instr(0xCA);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xCA);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iDex);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::dec);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[X], 0x0);
		ASSERT_EQ(registerMap[SR], 0x2);
	}
}
