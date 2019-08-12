
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class AbsoluteIndexedTest : public ::testing::Test {
	protected:

		AbsoluteIndexedTest() :
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

	TEST_F(AbsoluteIndexedTest, absYOra)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[Y] = 0x5;
		AbsoluteIndexed instr(0x19);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x3, 0x39);
		mem.writeByte(0x1239, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x19);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iOraY);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ora);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xAA);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);
	}

	TEST_F(AbsoluteIndexedTest, absYAnd)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[Y] = 0x5;
		AbsoluteIndexed instr(0x39);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x39);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iAndY);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::nnand);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xAA);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(AbsoluteIndexedTest, absYEor)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[Y] = 0x5;
		AbsoluteIndexed instr(0x59);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0x55);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x59);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iEorY);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::eor);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x55);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(AbsoluteIndexedTest, absYAdc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		registerMap[Y] = 0x5;
		AbsoluteIndexed instr(0x79);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x79);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iAdcY);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::adc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x1);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x03);
		ASSERT_EQ(registerMap[SR], 0x00);
	}

	TEST_F(AbsoluteIndexedTest, absYSta)
	{
		registerMap[AC] = 0xAC;
		registerMap[Y] = 0x5;
		AbsoluteIndexed instr(0x99);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x39, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x99);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iStaY);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x1239), 0xAC);
	}

	TEST_F(AbsoluteIndexedTest, absYLda)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xAC;
		registerMap[Y] = 0x5;
		AbsoluteIndexed instr(0xB9);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xB9);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iLdaY);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x2F);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(AbsoluteIndexedTest, absYCmp)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0;
		registerMap[Y] = 0x5;
		AbsoluteIndexed instr(0xD9);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xD9);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iCmpY);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x0);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(AbsoluteIndexedTest, absYSbc)
	{
		registerMap[Y] = 0x5;
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		AbsoluteIndexed instr(0xF9);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x1239, 0x1);
		mem.writeByte(0x2, 0x12);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xF9);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iSbcY);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sbc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x1);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(AbsoluteIndexedTest, absXLdy)
	{
		registerMap[SR] = 0xFF;
		registerMap[Y] = 0xAC;
		registerMap[X] = 0x5;
		AbsoluteIndexed instr(0xBC);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xBC);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iLdy);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x2F);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[Y], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(AbsoluteIndexedTest, absXOra)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[X] = 0x5;
		AbsoluteIndexed instr(0x1D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x3, 0x39);
		mem.writeByte(0x1239, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x1D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iOraX);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ora);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xAA);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);
	}
	
	TEST_F(AbsoluteIndexedTest, absXAnd)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[X] = 0x5;
		AbsoluteIndexed instr(0x3D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x3D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iAndX);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::nnand);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xAA);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}
	
	TEST_F(AbsoluteIndexedTest, absXEor)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[X] = 0x5;
		AbsoluteIndexed instr(0x5D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0x55);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x5D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iEorX);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::eor);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x55);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}
	
	TEST_F(AbsoluteIndexedTest, absXAdc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		registerMap[X] = 0x5;
		AbsoluteIndexed instr(0x7D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x7D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iAdcX);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::adc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x1);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x03);
		ASSERT_EQ(registerMap[SR], 0x00);
	}

	TEST_F(AbsoluteIndexedTest, absXSta)
	{
		registerMap[AC] = 0xAC;
		registerMap[X] = 0x5;
		AbsoluteIndexed instr(0x9D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x39, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x9D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iStaX);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x1239), 0xAC);
	}

	TEST_F(AbsoluteIndexedTest, absXLda)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xAC;
		registerMap[X] = 0x5;
		AbsoluteIndexed instr(0xBD);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xBD);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iLdaX);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x2F);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(AbsoluteIndexedTest, absXCmp)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0;
		registerMap[X] = 0x5;
		AbsoluteIndexed instr(0xDD);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xDD);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iCmpX);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x0);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(AbsoluteIndexedTest, absXSbc)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		AbsoluteIndexed instr(0xFD);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x1239, 0x1);
		mem.writeByte(0x2, 0x12);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xFD);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iSbcX);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sbc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x1239);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x1);
		ASSERT_EQ(instr.getAddress(), 0x1239);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(AbsoluteIndexedTest, absXAsl)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x00;
		AbsoluteIndexed instr(0x1E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x1E);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iAsl);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::asl);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getLowAddressByte(), 0x39);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getData(), 0x82);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(mem.readByte(0x1239), 0x82);
	}

	TEST_F(AbsoluteIndexedTest, absXRol)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x01;
		AbsoluteIndexed instr(0x3E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x3E);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iRol);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::rol);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getLowAddressByte(), 0x39);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getData(), 0x83);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(mem.readByte(0x1239), 0x83);
	}

	TEST_F(AbsoluteIndexedTest, absXLsr)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x00;
		AbsoluteIndexed instr(0x5E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x5E);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iLsr);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::lsr);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getLowAddressByte(), 0x39);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getData(), 0x60);
		ASSERT_EQ(registerMap[SR], 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(mem.readByte(0x1239), 0x60);
	}

	TEST_F(AbsoluteIndexedTest, absXRor)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x01;
		AbsoluteIndexed instr(0x7E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x7E);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iRor);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ror);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getLowAddressByte(), 0x39);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getData(), 0xE0);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(mem.readByte(0x1239), 0xE0);
	}

	TEST_F(AbsoluteIndexedTest, absYLdx)
	{
		registerMap[SR] = 0xFF;
		registerMap[X] = 0xAC;
		registerMap[Y] = 0xFF;
		AbsoluteIndexed instr(0xBE);
		PC++;
		mem.writeByte(0x1, 0x01);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1200, 0x30);
		mem.writeByte(0x1300, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xBE);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iLdx);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(PC, 3);
		ASSERT_EQ(instr.getLowAddressByte(), 0x00);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1200);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x30);
		ASSERT_EQ(instr.getAddress(), 0x1300);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x2F);
		ASSERT_EQ(instr.getAddress(), 0x1300);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(registerMap[X], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(AbsoluteIndexedTest, absXDec)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x00;
		AbsoluteIndexed instr(0xDE);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0x0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xDE);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iDec);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::dec);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getLowAddressByte(), 0x39);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getData(), 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(mem.readByte(0x1239), 0xFF);
	}

	TEST_F(AbsoluteIndexedTest, absXInc)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x00;
		AbsoluteIndexed instr(0xFE);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1239, 0xFF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xFE);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeAbsoluteIndexed::iInc);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsoluteIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::inc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getLowAddressByte(), 0x39);
		ASSERT_EQ(PC, 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xFF);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0xFF);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getData(), 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(mem.readByte(0x1239), 0x0);
	}
}
