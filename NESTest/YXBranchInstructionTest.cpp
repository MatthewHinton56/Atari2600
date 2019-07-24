#pragma once

#include "pch.h"

#include <chrono>


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
	
	TEST_F(YXBranchInstructionTest, BeqTest)
	{
		registerMap["SR"] = 0x02;
		PC = 0x100;
		YXBranchInstruction si
		(
			7,
			4,
			0,
			PC,
			0x80
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iBeq);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::relative);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x80);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x80);
		ASSERT_EQ(registerMap["SR"], 0x02);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(si.getCycles(), 4);

		ASSERT_EQ(PC, 0x82);
	}

	TEST_F(YXBranchInstructionTest, BneTest)
	{
		registerMap["SR"] = 0x02;
		PC = 0x100;
		YXBranchInstruction si
		(
			6,
			4,
			0,
			PC,
			0x80
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iBne);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::relative);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x80);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0);
		ASSERT_EQ(registerMap["SR"], 0x02);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(si.getCycles(), 2);

		ASSERT_EQ(PC, 0x102);
	}

	TEST_F(YXBranchInstructionTest, BccTest)
	{
		registerMap["SR"] = 0x00;
		PC = 0x100;
		YXBranchInstruction si
		(
			4,
			4,
			0,
			PC,
			0x10
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iBcc);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::relative);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x10);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x10);
		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(si.getCycles(), 3);

		ASSERT_EQ(PC, 0x112);
	}

	TEST_F(YXBranchInstructionTest, BcsTest)
	{
		registerMap["SR"] = 0x01;
		PC = 0x1FD;
		YXBranchInstruction si
		(
			5,
			4,
			0,
			PC,
			0x7F
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iBcs);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::relative);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);

		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x7F);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x7F);
		ASSERT_EQ(registerMap["SR"], 0x01);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(si.getCycles(), 4);

		ASSERT_EQ(PC, 0x27E);
	}

	TEST_F(YXBranchInstructionTest, StyZpgTest)
	{
		memory[0x7F] = 0xFF;
		registerMap["Y"] = 0x5A;
		YXBranchInstruction si
		(
			4,
			1,
			0,
			PC,
			0x7F
		);

		ASSERT_EQ(si.getInstruction(), YXBranchInstructions::iSty);
		ASSERT_EQ(si.getDecodeMode(), YXBranchInstructionAddressingMode::zeroPage);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 3);

		si.decode(registerMap, memory);

		ASSERT_EQ(si.getAddress(), 0x7F);
		ASSERT_EQ(si.getDecodeVal(), 0x5A);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x5A);

		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory[0x7F], 0x5A);

		PC = si.pc();

		ASSERT_EQ(si.getCycles(), 3);

		ASSERT_EQ(PC, 2);
	}

}
