
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class AbsoluteTest : public ::testing::Test {
	protected:

		AbsoluteTest() :
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

	TEST_F(AbsoluteTest, absBit)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xFF;
		Absolute instr(0x2C);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x2C);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iBit);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::bit);
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
		ASSERT_EQ(instr.getData(), 0xBF);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[SR], 0xBD);
	}

	TEST_F(AbsoluteTest, absJmp)
	{
		Absolute instr(0x4C);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x4C);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iJmp);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::jmp);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::jmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getHighAddressByte(), 0x12);
		ASSERT_EQ(instr.getAddress(), 0x1234);
		ASSERT_EQ(PC, 0x1234);
	}

	TEST_F(AbsoluteTest, absSty)
	{
		registerMap[Y] = 0xAC;
		Absolute instr(0x8C);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x8C);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iSty);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::write);
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

	TEST_F(AbsoluteTest, absLdy)
	{
		registerMap[SR] = 0xFF;
		registerMap[Y] = 0xAC;
		Absolute instr(0xAC);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xAC);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iLdy);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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
		ASSERT_EQ(registerMap[Y], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(AbsoluteTest, absCpy)
	{
		registerMap[SR] = 0x00;
		registerMap[Y] = 0;
		Absolute instr(0xCC);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xCC);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iCpy);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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
		ASSERT_EQ(registerMap[Y], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(AbsoluteTest, absCpx)
	{
		registerMap[SR] = 0x00;
		registerMap[X] = 0;
		Absolute instr(0xEC);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xEC);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iCpx);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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
		ASSERT_EQ(registerMap[X], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(AbsoluteTest, absOra)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		Absolute instr(0x0D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x0D);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iOra);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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

	TEST_F(AbsoluteTest, absAnd)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		Absolute instr(0x2D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x2D);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iAnd);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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

	TEST_F(AbsoluteTest, absEor)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		Absolute instr(0x4D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x55);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x4D);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iEor);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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

	TEST_F(AbsoluteTest, absAdc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		Absolute instr(0x6D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x6D);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iAdc);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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

	TEST_F(AbsoluteTest, absSta)
	{
		registerMap[AC] = 0xAC;
		Absolute instr(0x8D);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x8D);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iSta);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::write);
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

	TEST_F(AbsoluteTest, absLda)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xAC;
		Absolute instr(0xAD);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xAD);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iLda);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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

	TEST_F(AbsoluteTest, absCmp)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0;
		Absolute instr(0xCD);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xCD);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iCmp);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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

	TEST_F(AbsoluteTest, absSbc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		Absolute instr(0xED);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xED);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iSbc);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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

	TEST_F(AbsoluteTest, absAsl)
	{
		registerMap[SR] = 0x00;
		Absolute instr(0x0E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x0E);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iAsl);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::rmw);
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

	TEST_F(AbsoluteTest, absRol)
	{
		registerMap[SR] = 0x01;
		Absolute instr(0x2E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x2E);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iRol);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::rmw);
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

	TEST_F(AbsoluteTest, absLsr)
	{
		registerMap[SR] = 0x00;
		Absolute instr(0x4E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x4E);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iLsr);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::rmw);
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

	TEST_F(AbsoluteTest, absRor)
	{
		registerMap[SR] = 0x01;
		Absolute instr(0x6E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x6E);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iRor);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::rmw);
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

	TEST_F(AbsoluteTest, absStx)
	{
		registerMap[X] = 0xAC;
		Absolute instr(0x8E);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x8E);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iStx);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::write);
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

	TEST_F(AbsoluteTest, absLdx)
	{
		registerMap[SR] = 0xFF;
		registerMap[X] = 0xAC;
		Absolute instr(0xAE);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xAE);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iLdx);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::read);
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

	TEST_F(AbsoluteTest, absDec)
	{
		registerMap[SR] = 0x00;
		Absolute instr(0xCE);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0x0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xCE);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iDec);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::rmw);
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

	TEST_F(AbsoluteTest, absInc)
	{
		registerMap[SR] = 0x00;
		Absolute instr(0xEE);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x1234, 0xFF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xEE);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeAbsolute::iInc);
		ASSERT_EQ(instr.getType(), InstructionTypeAbsolute::rmw);
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
	}
}
