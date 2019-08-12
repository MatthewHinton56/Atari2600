
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class ZeropageTest : public ::testing::Test {
	protected:

		ZeropageTest() :
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

	TEST_F(ZeropageTest, zpgBit)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xFF;
		Zeropage instr(0x24);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x34, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x24);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iBit);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::bit);
		ASSERT_EQ(PC, 1);


		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0xBF);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[SR], 0xBD);
	}

	TEST_F(ZeropageTest, zpgSty)
	{
		registerMap[Y] = 0xAC;
		Zeropage instr(0x84);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x34, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x84);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iSty);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(mem.readByte(0x34), 0xAC);
	}

	TEST_F(ZeropageTest, zpgLdy)
	{
		registerMap[SR] = 0xFF;
		registerMap[Y] = 0xAC;
		Zeropage instr(0xA4);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xA4);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iLdy);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[Y], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(ZeropageTest, zpgCpy)
	{
		registerMap[SR] = 0x00;
		registerMap[Y] = 0;
		Zeropage instr(0xC4);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xC4);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iCpy);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[Y], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ZeropageTest, zpgCpx)
	{
		registerMap[SR] = 0x00;
		registerMap[X] = 0;
		Zeropage instr(0xE4);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xE4);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iCpx);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[X], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ZeropageTest, zpgOra)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		Zeropage instr(0x05);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x05);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iOra);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ora);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[AC], 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);
	}

	TEST_F(ZeropageTest, zpgAnd)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		Zeropage instr(0x25);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0xAA);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x25);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iAnd);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::nnand);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0xAA);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(ZeropageTest, zpgEor)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0x55;
		Zeropage instr(0x45);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0x55);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x45);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iEor);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::eor);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x55);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);
	}

	TEST_F(ZeropageTest, zpgAdc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		Zeropage instr(0x65);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x65);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iAdc);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::adc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[AC], 0x03);
		ASSERT_EQ(registerMap[SR], 0x00);
	}

	TEST_F(ZeropageTest, zpgSta)
	{
		registerMap[AC] = 0xAC;
		Zeropage instr(0x85);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x85);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iSta);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(mem.readByte(0x34), 0xAC);
	}

	TEST_F(ZeropageTest, zpgLda)
	{
		registerMap[SR] = 0xFF;
		registerMap[AC] = 0xAC;
		Zeropage instr(0xA5);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xA5);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iLda);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[AC], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(ZeropageTest, zpgCmp)
	{
		registerMap[SR] = 0x00;
		registerMap[AC] = 0;
		Zeropage instr(0xC5);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xC5);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iCmp);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cmp);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x0);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[AC], 0x0);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ZeropageTest, zpgSbc)
	{
		registerMap[SR] = 0x01;
		registerMap[AC] = 0x01;
		Zeropage instr(0xE5);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0x1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xE5);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iSbc);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sbc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[AC], 0x00);
		ASSERT_EQ(registerMap[SR], 0x03);
	}

	TEST_F(ZeropageTest, zpgAsl)
	{
		registerMap[SR] = 0x00;
		Zeropage instr(0x06);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x06);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iAsl);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::asl);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x82);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x34), 0x82);
	}

	TEST_F(ZeropageTest, zpgRol)
	{
		registerMap[SR] = 0x01;
		Zeropage instr(0x26);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x26);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iRol);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::rol);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x83);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x34), 0x83);
	}

	TEST_F(ZeropageTest, zpgLsr)
	{
		registerMap[SR] = 0x00;
		Zeropage instr(0x46);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x46);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iLsr);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::lsr);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x60);
		ASSERT_EQ(registerMap[SR], 0x01);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x34), 0x60);
	}

	TEST_F(ZeropageTest, zpgRor)
	{
		registerMap[SR] = 0x01;
		Zeropage instr(0x66);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0xC1);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x66);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iRor);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ror);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0xC1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xE0);
		ASSERT_EQ(registerMap[SR], 0x81);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x34), 0xE0);
	}

	TEST_F(ZeropageTest, zpgStx)
	{
		registerMap[X] = 0xAC;
		Zeropage instr(0x86);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0xBF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x86);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iStx);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::write);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::st);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(mem.readByte(0x34), 0xAC);
	}

	TEST_F(ZeropageTest, zpgLdx)
	{
		registerMap[SR] = 0xFF;
		registerMap[X] = 0xAC;
		Zeropage instr(0xA6);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0x2F);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xA6);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iLdx);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::read);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x2F);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[X], 0x2F);
		ASSERT_EQ(registerMap[SR], 0x7D);
	}

	TEST_F(ZeropageTest, zpgDec)
	{
		registerMap[SR] = 0x00;
		Zeropage instr(0xC6);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0x0);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xC6);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iDec);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::dec);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0x00);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0xFF);
		ASSERT_EQ(registerMap[SR], 0x80);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x34), 0xFF);
	}

	TEST_F(ZeropageTest, zpgInc)
	{
		registerMap[SR] = 0x00;
		Zeropage instr(0xE6);
		PC++;
		mem.writeByte(0x1, 0x34);
		mem.writeByte(0x2, 0x12);
		mem.writeByte(0x34, 0xFF);
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xE6);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeZeropage::iInc);
		ASSERT_EQ(instr.getType(), InstructionTypeZeropage::rmw);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::inc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x34);
		ASSERT_EQ(instr.getAddress(), 0x34);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(instr.getData(), 0xFF);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(instr.getData(), 0x00);
		ASSERT_EQ(registerMap[SR], 0x02);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x34), 0x00);
	}
}
