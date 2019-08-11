
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class ZeropageIndexedTest : public ::testing::Test {
	protected:

		ZeropageIndexedTest() :
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

	TEST_F(ZeropageIndexedTest, zpgISty)
	{
		registerMap[Y] = 0xAC;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0x94);
		PC++;
		mem.writeByte(0x1, 0xFF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x94);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iSty);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0xFF);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x4);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(mem.readByte(0x4), 0xAC);
	}

	TEST_F(ZeropageIndexedTest, zpgILdy)
	{
		registerMap[SR] = 0xFF;
		registerMap[Y] = 0xAC;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0xB4);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xB4);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iLdy);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x39);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[Y], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}
	/*
	TEST_F(ZeropageIndexedTest, zpgIOra)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		ZeropageIndexed instr(0x0D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x0D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iOra);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ora);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);
	}

	TEST_F(ZeropageIndexedTest, zpgIAnd)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		ZeropageIndexed instr(0x2D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x2D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iAnd);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::nnand);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(ZeropageIndexedTest, zpgIEor)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		ZeropageIndexed instr(0x4D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x55);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x4D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iEor);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::eor);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x55);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(ZeropageIndexedTest, zpgIAdc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		ZeropageIndexed instr(0x6D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x6D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iAdc);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::adc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x03);
		ASSERT_EQ(registerMap[SR], 0x00);
	}

	TEST_F(ZeropageIndexedTest, zpgISta)
	{
		registerMap[AC] = 0xAC;
		ZeropageIndexed instr(0x8D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x8D);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iSta);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(mem.readByte(0x1234), 0xAC);
	}

	TEST_F(ZeropageIndexedTest, zpgILda)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xAC;
		ZeropageIndexed instr(0xAD);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xAD);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iLda);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(ZeropageIndexedTest, zpgICmp)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0;
		ZeropageIndexed instr(0xCD);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xCD);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iCmp);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ZeropageIndexedTest, zpgISbc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		ZeropageIndexed instr(0xED);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xED);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iSbc);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sbc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ZeropageIndexedTest, zpgIAsl)
	{
		registerMap[SR] = 0x00;
		ZeropageIndexed instr(0x0E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x0E);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iAsl);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::asl);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x82);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x1234), 0x82);
	}

	TEST_F(ZeropageIndexedTest, zpgIRol)
	{
		registerMap[SR] = 0x01;
		ZeropageIndexed instr(0x2E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x2E);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iRol);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::rol);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x83);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x1234), 0x83);
	}

	TEST_F(ZeropageIndexedTest, zpgILsr)
	{
		registerMap[SR] = 0x00;
		ZeropageIndexed instr(0x4E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x4E);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iLsr);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::lsr);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x60);
		ASSERT_EQ(registerMap[SR], 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x1234), 0x60);
	}

	TEST_F(ZeropageIndexedTest, zpgIRor)
	{
		registerMap[SR] = 0x01;
		ZeropageIndexed instr(0x6E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x6E);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iRor);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ror);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0xE0);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x1234), 0xE0);
	}

	TEST_F(ZeropageIndexedTest, zpgIStx)
	{
		registerMap[X] = 0xAC;
		ZeropageIndexed instr(0x8E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x8E);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iStx);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(mem.readByte(0x1234), 0xAC);
	}

	TEST_F(ZeropageIndexedTest, zpgILdx)
	{
		registerMap[SR] = 0xFF;
		registerMap[X] = 0xAC;
		ZeropageIndexed instr(0xAE);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xAE);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iLdx);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[X], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(ZeropageIndexedTest, zpgIDec)
	{
		registerMap[SR] = 0x00;
		ZeropageIndexed instr(0xCE);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xCE);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iDec);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::dec);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x00);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x1234), 0xFF);
	}

	TEST_F(ZeropageIndexedTest, zpgIInc)
	{
		registerMap[SR] = 0x00;
		ZeropageIndexed instr(0xEE);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xFF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xEE);
		ASSERT_EQ(instr.getInstrucion(), InstructionOpcodeZeropageIndexed::iInc);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::inc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xFF);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x1234), 0x00);
	}*/
}
