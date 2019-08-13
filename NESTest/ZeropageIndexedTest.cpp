
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

	TEST_F(ZeropageIndexedTest, zpgXSty)
	{
		registerMap[Y] = 0xAC;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0x94);
		PC++;
		mem.writeByte(0x1, 0xFF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x94);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iSty);
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

	TEST_F(ZeropageIndexedTest, zpgXLdy)
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
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iLdy);
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

	TEST_F(ZeropageIndexedTest, zpgXOra)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0x15);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x39, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x15);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iOra);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ora);
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
		ASSERT_EQ(instr.getData(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);
	}
	
	TEST_F(ZeropageIndexedTest, zpgXAnd)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0x35);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x35);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iAnd);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::nnand);
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
		ASSERT_EQ(instr.getData(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}
	
	TEST_F(ZeropageIndexedTest, zpgXEor)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0x55);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x39, 0x55);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x55);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iEor);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::eor);
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
		ASSERT_EQ(instr.getData(), 0x55);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}
	
	TEST_F(ZeropageIndexedTest, zpgXAdc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0x75);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x75);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iAdc);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::adc);
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
		ASSERT_EQ(instr.getData(), 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x03);
		ASSERT_EQ(registerMap[SR], 0x00);
	}

	TEST_F(ZeropageIndexedTest, zpgXSta)
	{
		registerMap[AC] = 0xAC;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0x95);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x95);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iSta);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x39);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(mem.readByte(0x39), 0xAC);
	}

	TEST_F(ZeropageIndexedTest, zpgXLda)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xAC;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0xB5);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xB5);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iLda);
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
		ASSERT_EQ(registerMap[AC], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(ZeropageIndexedTest, zpgXCmp)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0;
		registerMap[X] = 0x5;
		ZeropageIndexed instr(0xD5);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xD5);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iCmp);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
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
		ASSERT_EQ(instr.getData(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ZeropageIndexedTest, zpgXSbc)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		ZeropageIndexed instr(0xF5);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xF5);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iSbc);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sbc);
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
		ASSERT_EQ(instr.getData(), 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ZeropageIndexedTest, zpgXAsl)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x00;
		ZeropageIndexed instr(0x16);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x16);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iAsl);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::asl);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x39);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x82);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x39), 0x82);
	}

	TEST_F(ZeropageIndexedTest, zpgXRol)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x01;
		ZeropageIndexed instr(0x36);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x36);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iRol);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::rol);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x39);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x83);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x39), 0x83);
	}

	TEST_F(ZeropageIndexedTest, zpgXLsr)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x00;
		ZeropageIndexed instr(0x56);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x56);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iLsr);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::lsr);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x39);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x60);
		ASSERT_EQ(registerMap[SR], 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x39), 0x60);
	}

	TEST_F(ZeropageIndexedTest, zpgXRor)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x01;
		ZeropageIndexed instr(0x76);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x76);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iRor);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ror);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x39);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0xE0);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x39), 0xE0);
	}

	TEST_F(ZeropageIndexedTest, zpgYStx)
	{
		registerMap[Y] = 0x5;
		registerMap[X] = 0xAC;
		ZeropageIndexed instr(0x96);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x96);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iStx);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x39);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(mem.readByte(0x39), 0xAC);
	}

	TEST_F(ZeropageIndexedTest, zpgYLdx)
	{
		registerMap[SR] = 0xFF;
		registerMap[X] = 0xAC;
		registerMap[Y] = 0x5;
		ZeropageIndexed instr(0xB6);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xB6);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iLdx);
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
		ASSERT_EQ(registerMap[X], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(ZeropageIndexedTest, zpgXDec)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x00;
		ZeropageIndexed instr(0xD6);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0x0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xD6);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iDec);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::dec);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x39);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x00);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x39), 0xFF);
	}

	TEST_F(ZeropageIndexedTest, zpgXInc)
	{
		registerMap[X] = 0x5;
		registerMap[SR] = 0x00;
		ZeropageIndexed instr(0xF6);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x39, 0xFF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xF6);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropageIndexed::iInc);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropageIndexed::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::inc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getAddress(), 0x39);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xFF);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(instr.getData(), 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(mem.readByte(0x39), 0x00);
	}
}
