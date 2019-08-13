
#pragma once

#include "pch.h"

#include <chrono>

using namespace mos6502;

namespace {

	class ImmediateTest : public ::testing::Test {
	protected:

		ImmediateTest() :
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

	TEST_F(ImmediateTest, immLdy)
	{
		registerMap[SR] = 0xFF;
		registerMap[Y] = 0xAC;
		Immediate instr(0xA0);
		PC++;
		mem.writeByte(0x1, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xA0);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iLdy);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[Y], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(ImmediateTest, immCpy)
	{
		registerMap[SR] = 0x00;
		registerMap[Y] = 0;
		registerMap[AC] = 0xFF;
		registerMap[X] = 0xFF;
		Immediate instr(0xC0);
		PC++;
		mem.writeByte(0x1, 0x0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xC0);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iCpy);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[Y], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ImmediateTest, immCpx)
	{
		registerMap[SR] = 0x00;
		registerMap[X] = 0;
		registerMap[AC] = 0xFF;
		registerMap[Y] = 0xFF;
		Immediate instr(0xE0);
		PC++;
		mem.writeByte(0x1, 0x0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xE0);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iCpx);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[X], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ImmediateTest, immOra)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		Immediate instr(0x09);
		PC++;
		mem.writeByte(0x1, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x09);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iOra);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ora);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);
	}

	TEST_F(ImmediateTest, immAnd)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		Immediate instr(0x29);
		PC++;
		mem.writeByte(0x1, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x29);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iAnd);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::nnand);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(ImmediateTest, immEor)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		Immediate instr(0x49);
		PC++;
		mem.writeByte(0x1, 0x55);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x49);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iEor);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::eor);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x55);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(ImmediateTest, immAdc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		Immediate instr(0x69);
		PC++;
		mem.writeByte(0x1, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x69);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iAdc);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::adc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x03);
		ASSERT_EQ(registerMap[SR], 0x00);
	}

	TEST_F(ImmediateTest, immLda)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xAC;
		Immediate instr(0xA9);
		PC++;
		mem.writeByte(0x1, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xA9);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iLda);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(ImmediateTest, immCmp)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0;
		Immediate instr(0xC9);
		PC++;
		mem.writeByte(0x1, 0x0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xC9);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iCmp);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}
	
	TEST_F(ImmediateTest, immSbc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		Immediate instr(0xE9);
		PC++;
		mem.writeByte(0x1, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xE9);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iSbc);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sbc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ImmediateTest, immLdx)
	{
		registerMap[SR] = 0xFF;
		registerMap[X] = 0xAC;
		Immediate instr(0xA2);
		PC++;
		mem.writeByte(0x1, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xA2);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImmediate::iLdx);
		ASSERT_EQ(instr.getType(), InstructionTypeImmediate::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[X], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}
}
