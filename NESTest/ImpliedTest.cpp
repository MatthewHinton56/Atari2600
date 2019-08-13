
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

	TEST_F(ImpliedTest, implNop)
	{
		registerMap[X] = 0x1;
		registerMap[SR] = 0x0;
		Implied instr(0xEA);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xEA);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iNop);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::nop);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[X], 0x1);
		ASSERT_EQ(registerMap[SR], 0x0);
	}

	TEST_F(ImpliedTest, implClc)
	{
		registerMap[SR] = 0xFF;
		Implied instr(0x18);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x18);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iClc);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::clc);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SR], 0xFE);
	}

	TEST_F(ImpliedTest, implSec)
	{
		registerMap[SR] = 0x00;
		Implied instr(0x38);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x38);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iSec);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sec);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SR], 0x01);
	}

	TEST_F(ImpliedTest, implCli)
	{
		registerMap[SR] = 0xFF;
		Implied instr(0x58);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x58);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iCli);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cli);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SR], 0xFB);
	}

	TEST_F(ImpliedTest, implSei)
	{
		registerMap[SR] = 0x00;
		Implied instr(0x78);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x78);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iSei);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sei);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SR], 0x04);
	}

	TEST_F(ImpliedTest, implTya)
	{
		registerMap[AC] = 0xBC;
		registerMap[Y] = 0x32;
		registerMap[SR] = 0x0;
		Implied instr(0x98);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x98);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iTya);
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

	TEST_F(ImpliedTest, implClv)
	{
		registerMap[SR] = 0xFF;
		Implied instr(0xB8);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xB8);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iClv);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::clv);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SR], 0xBF);
	}

	TEST_F(ImpliedTest, implCld)
	{
		registerMap[SR] = 0xFF;
		Implied instr(0xD8);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xD8);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iCld);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::cld);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SR], 0xF7);
	}

	TEST_F(ImpliedTest, implSed)
	{
		registerMap[SR] = 0x00;
		Implied instr(0xF8);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xF8);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iSed);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::sed);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SR], 0x08);
	}

	TEST_F(ImpliedTest, implTxs)
	{
		registerMap[SP] = 0xBC;
		registerMap[X] = 0x32;
		registerMap[SR] = 0x0;
		Implied instr(0x9A);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0x9A);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iTxs);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::trf);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SP], 0x32);
		ASSERT_EQ(registerMap[SR], 0x00);
	}


	TEST_F(ImpliedTest, implTsx)
	{
		registerMap[X] = 0xBC;
		registerMap[SP] = 0x32;
		registerMap[SR] = 0x0;
		Implied instr(0xBA);
		PC++;
		ASSERT_EQ(instr.getStepCount(), 1);
		ASSERT_EQ(instr.getOpcode(), 0xBA);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeImplied::iTsx);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::trf);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 2);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SP], 0x32);
		ASSERT_EQ(registerMap[SR], 0x00);
	}
}
