#pragma once

#include "pch.h"


#define COMMA ,

using namespace mos6502;

namespace {

	class XDecIncInstructionTest : public ::testing::Test {
	protected:

		XDecIncInstructionTest() :
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

	//AND - xIndirect SR = 0
	TEST_F(XDecIncInstructionTest, TXATest)
	{
		registerMap["X"] = 0x80;
		registerMap["A"] = 0xFF;

		XDecIncInstruction si
		(
			4,
			2,
			2,
			PC
		);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iTxa);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x80);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x80);
		ASSERT_EQ(registerMap["SR"], 0x80);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0x80);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(XDecIncInstructionTest, TXSTest)
	{
		registerMap["X"] = 0x71;
		registerMap["SP"] = 0xFF;

		XDecIncInstruction si
		(
			4,
			6,
			2,
			PC
		);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iTxs);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x71);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x71);
		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["SP"], 0x71);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(XDecIncInstructionTest, TAXTest)
	{
		registerMap["X"] = 0x80;
		registerMap["A"] = 0x00;

		XDecIncInstruction si
		(
			5,
			2,
			2,
			PC
		);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iTax);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x00);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x02);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["X"], 0x00);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(XDecIncInstructionTest, TSXTest)
	{
		registerMap["X"] = 0x71;
		registerMap["SP"] = 0xAC;

		XDecIncInstruction si
		(
			5,
			6,
			2,
			PC
		);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iTsx);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0xAC);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xAc);
		ASSERT_EQ(registerMap["SR"], 0x80);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["X"], 0xAC);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(XDecIncInstructionTest, DEXTest)
	{
		registerMap["X"] = 0x01;

		XDecIncInstruction si
		(
			6,
			2,
			2,
			PC
		);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iDex);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::implied);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x01);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x02);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["X"], 0x00);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(XDecIncInstructionTest, NOPTest)
	{
		XDecIncInstruction si
		(
			7,
			2,
			2,
			PC
		);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iNop);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::implied);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x0);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["X"], 0x0);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(XDecIncInstructionTest, absYLDX)
	{
		registerMap["Y"] = 0xAA;

		memory[0x10A] = 0x85;

		XDecIncInstruction si
		(
			5,
			7,
			2,
			PC,
			0x60
		);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iLdx);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::absoluteY);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 4);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x10A);
		ASSERT_EQ(si.getDecodeVal(), 0x85);

		ASSERT_EQ(si.getCycles(), 5);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x85);
		ASSERT_EQ(registerMap["SR"], 0x80);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["X"], 0x85);

		PC = si.pc();

		ASSERT_EQ(PC, 3);
	}

	TEST_F(XDecIncInstructionTest, zpgYSTX)
	{
		registerMap["Y"] = 0x40;
		registerMap["X"] = 0x65;

		memory[0x40] = 0xFF;

		XDecIncInstruction si
		(
			4,
			5,
			2,
			PC,
			0x0
		);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iStx);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::yZeroPage);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 4);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x40);
		ASSERT_EQ(si.getDecodeVal(), 0x65);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x65);
		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory[0x40], 0x65);

		PC = si.pc();

		ASSERT_EQ(PC, 2);
	}

	TEST_F(XDecIncInstructionTest, immLDX)
	{
		registerMap["X"] = 0xFF;

		XDecIncInstruction si
		(
			5,
			0,
			2,
			PC,
			0xCA
		);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iLdx);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::immediate);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0xCA);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xCA);
		ASSERT_EQ(registerMap["SR"], 0x80);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["X"], 0xCA);

		PC = si.pc();

		ASSERT_EQ(PC, 2);
	}

	TEST_F(XDecIncInstructionTest, zpgDEC)
	{
		memory[0xDD] = 0x1;

		XDecIncInstruction si
		(
			6,
			1,
			2,
			PC,
			0xDD
		);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iDec);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::zeroPage);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 5);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0xDD);
		ASSERT_EQ(si.getDecodeVal(), 0x1);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x0);
		ASSERT_EQ(registerMap["SR"], 0x02);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory[0xDD], 0x00);

		PC = si.pc();

		ASSERT_EQ(PC, 2);
	}

	TEST_F(XDecIncInstructionTest, absINC)
	{
		memory[0xFFF] = 0x7F;

		XDecIncInstruction si
		(
			7,
			3,
			2,
			PC,
			0xFF,
			0xF
		);

		ASSERT_EQ(si.getInstruction(), XDecIncInstructions::iInc);
		ASSERT_EQ(si.getDecodeMode(), InstructionAddressingMode::absolute);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 6);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0xFFF);
		ASSERT_EQ(si.getDecodeVal(), 0x7F);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x80);
		ASSERT_EQ(registerMap["SR"], 0x80);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory[0xFFF], 0x80);

		PC = si.pc();

		ASSERT_EQ(PC, 3);
	}
}
