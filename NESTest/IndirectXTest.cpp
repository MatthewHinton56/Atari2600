
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class IndirectXTest : public ::testing::Test {
	protected:

		IndirectXTest() :
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

	TEST_F(IndirectXTest, indXOra)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[X] = 0x5;
		IndirectX instr(0x01);
		PC++;
		mem.writeByte(0x1, 0xC);
		mem.writeByte(0x11, 0x34);
		mem.writeByte(0x12, 0x12);
		mem.writeByte(0x1234, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x01);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeIndirectX::iOra);
		ASSERT_EQ(instr.getType(), InstructionTypeIndirectX::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ora);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getPointer(), 0xC);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getPointer(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getPointer(), 0x11);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getAddress(), 0x1234);
		ASSERT_EQ(instr.getData(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(registerMap[AC], 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);
	}

	TEST_F(IndirectXTest, indXAnd)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[X] = 0x5;
		IndirectX instr(0x21);
		PC++;
		mem.writeByte(0x1, 0xC);
		mem.writeByte(0x11, 0x34);
		mem.writeByte(0x12, 0x12);
		mem.writeByte(0x1234, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x21);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeIndirectX::iAnd);
		ASSERT_EQ(instr.getType(), InstructionTypeIndirectX::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::nnand);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getPointer(), 0xC);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getPointer(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getPointer(), 0x11);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getAddress(), 0x1234);
		ASSERT_EQ(instr.getData(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(IndirectXTest, indXEor)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[X] = 0x5;
		IndirectX instr(0x41);
		PC++;
		mem.writeByte(0x1, 0xC);
		mem.writeByte(0x11, 0x34);
		mem.writeByte(0x12, 0x12);
		mem.writeByte(0x1234, 0x55);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x41);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeIndirectX::iEor);
		ASSERT_EQ(instr.getType(), InstructionTypeIndirectX::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::eor);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getPointer(), 0xC);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getPointer(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getPointer(), 0x11);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getAddress(), 0x1234);
		ASSERT_EQ(instr.getData(), 0x55);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(IndirectXTest, indXAdc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		registerMap[X] = 0x5;
		IndirectX instr(0x61);
		PC++;
		mem.writeByte(0x1, 0xC);
		mem.writeByte(0x11, 0x34);
		mem.writeByte(0x12, 0x12);
		mem.writeByte(0x1234, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x61);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeIndirectX::iAdc);
		ASSERT_EQ(instr.getType(), InstructionTypeIndirectX::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::adc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getPointer(), 0xC);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getPointer(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getPointer(), 0x11);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getAddress(), 0x1234);
		ASSERT_EQ(instr.getData(), 0x1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(registerMap[AC], 0x03);
		ASSERT_EQ(registerMap[SR], 0x00);
	}

	TEST_F(IndirectXTest, indXSta)
	{
		registerMap[AC] = 0xAC;
		registerMap[X] = 0x5;
		IndirectX instr(0x81);
		PC++;
		mem.writeByte(0x1, 0xC);
		mem.writeByte(0x11, 0x34);
		mem.writeByte(0x12, 0x12);
		mem.writeByte(0x1234, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x81);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeIndirectX::iSta);
		ASSERT_EQ(instr.getType(), InstructionTypeIndirectX::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getPointer(), 0xC);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getPointer(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getPointer(), 0x11);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getAddress(), 0x1234);
		ASSERT_EQ(mem.readByte(0x1234), 0xAC);
	}

	TEST_F(IndirectXTest, indXLda)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xAC;
		registerMap[X] = 0x5;
		IndirectX instr(0xA1);
		PC++;
		mem.writeByte(0x1, 0xC);
		mem.writeByte(0x11, 0x34);
		mem.writeByte(0x12, 0x12);
		mem.writeByte(0x1234, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xA1);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeIndirectX::iLda);
		ASSERT_EQ(instr.getType(), InstructionTypeIndirectX::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getPointer(), 0xC);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getPointer(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getPointer(), 0x11);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getAddress(), 0x1234);
		ASSERT_EQ(instr.getData(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(registerMap[AC], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(IndirectXTest, indXCmp)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0;
		registerMap[X] = 0x5;
		IndirectX instr(0xC1);
		PC++;
		mem.writeByte(0x1, 0xC);
		mem.writeByte(0x11, 0x34);
		mem.writeByte(0x12, 0x12);
		mem.writeByte(0x1234, 0x0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xC1);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeIndirectX::iCmp);
		ASSERT_EQ(instr.getType(), InstructionTypeIndirectX::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getPointer(), 0xC);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getPointer(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getPointer(), 0x11);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getAddress(), 0x1234);
		ASSERT_EQ(instr.getData(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(registerMap[AC], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(IndirectXTest, indXSbc)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		IndirectX instr(0xE1);
		PC++;
		mem.writeByte(0x1, 0xC);
		mem.writeByte(0x11, 0x34);
		mem.writeByte(0x12, 0x12);
		mem.writeByte(0x1234, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xE1);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeIndirectX::iSbc);
		ASSERT_EQ(instr.getType(), InstructionTypeIndirectX::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sbc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getPointer(), 0xC);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getPointer(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getPointer(), 0x11);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getAddress(), 0x1234);
		ASSERT_EQ(instr.getData(), 0x1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x03);
	}
}
