#pragma once

#include "pch.h"


#define COMMA ,

using namespace mos6502;

namespace {

	class YXBranchInstructionTest : public ::testing::Test {
	protected:

		YXBranchInstructionTest() :
			memory(),
			registerMap(),
			PC(0)
		{}


		void SetUp() override
		{
			registerMap["A"] = 0;
			registerMap["X"] = 0;
			registerMap["Y"] = 0;
			registerMap["SR"] = 0;
			registerMap["SP"] = 0;
		}

		MemoryAccessor memory;
		RegisterMap registerMap;
		Word PC;
	};

	TEST_F(YXBranchInstructionTest, DeyTest)
	{
		registerMap["Y"] = 0x01;

		YXBranchInstruction si
		(
			4,
			2,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iDey);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x01);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x02);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["Y"], 0x00);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(YXBranchInstructionTest, TayTest)
	{
		registerMap["A"] = 0xBC;
		registerMap["Y"] = 0xCA;

		YXBranchInstruction si
		(
			5,
			2,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iTay);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0xBC);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xBC);
		ASSERT_EQ(registerMap["SR"], 0x80);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["Y"], 0xBC);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(YXBranchInstructionTest, InyTest)
	{
		registerMap["Y"] = 0xFF;

		YXBranchInstruction si
		(
			6,
			2,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iIny);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0xFF);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x02);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["Y"], 0x00);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(YXBranchInstructionTest, InxTest)
	{
		registerMap["X"] = 0x01;

		YXBranchInstruction si
		(
			7,
			2,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iInx);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x01);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x2);
		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["X"], 0x02);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(YXBranchInstructionTest, TyaTest)
	{
		registerMap["Y"] = 0x01;
		registerMap["A"] = 0xFE;

		YXBranchInstruction si
		(
			4,
			6,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iTya);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x01);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x01);
		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0x01);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(YXBranchInstructionTest, ClvTest)
	{
		registerMap["SR"] = 0x40;

		YXBranchInstruction si
		(
			5,
			6,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iClv);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0);
		ASSERT_EQ(registerMap["SR"], 0);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["Y"], 0);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(YXBranchInstructionTest, CldTest)
	{
		registerMap["SR"] = 0x08;

		YXBranchInstruction si
		(
			6,
			6,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iCld);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x0);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["Y"], 0x00);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}
	
	TEST_F(YXBranchInstructionTest, SedTest)
	{
		YXBranchInstruction si
		(
			7,
			6,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iSed);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x8);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["Y"], 0x00);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}
}
