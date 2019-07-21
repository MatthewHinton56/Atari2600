#pragma once

#include "pch.h"


#define COMMA ,

using namespace mos6507;

namespace {

	class StandardInstructionTest : public ::testing::Test {
	protected:

		StandardInstructionTest() :
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
	TEST_F(StandardInstructionTest, XIndirectTestAND)
	{
		memory[0x00] = 0x01;
		memory[0x01] = 0x02;
		memory[0x201] = 0xCA;
		registerMap["X"] = 0x80;
		registerMap["A"] = 0xFF;
		
		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iAnd),
			InstructionAddressingMode::xIndirect,
			PC,
			0x80
		);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 6);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x201);
		ASSERT_EQ(si.getDecodeVal(), 0xCA);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xCA);
		ASSERT_EQ(registerMap["SR"], 0x80);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0xCA);

		PC = si.pc();

		ASSERT_EQ(PC, 2);
	}

	TEST_F(StandardInstructionTest, zpgADD)
	{
		memory[0x80] = 0x24;
		registerMap["A"] = 0x23;

		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iAdc),
			InstructionAddressingMode::zeroPage,
			PC,
			0x80
		);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 3);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x80);
		ASSERT_EQ(si.getDecodeVal(), 0x24);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x47);
		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0x47);

		PC = si.pc();

		ASSERT_EQ(PC, 2);
	}

	TEST_F(StandardInstructionTest, immLDA)
	{

		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iLda),
			InstructionAddressingMode::immediate,
			PC,
			0xF7
		);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0xF7);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xF7);
		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0xF7);

		PC = si.pc();

		ASSERT_EQ(PC, 2);
	}

	TEST_F(StandardInstructionTest, absSTA)
	{
		registerMap["A"] = 0x56;
		memory[0x1F7] = 0xFF;

		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iSta),
			InstructionAddressingMode::absolute,
			PC,
			0xF7,
			0x01
		);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 4);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x1F7);
		ASSERT_EQ(si.getDecodeVal(), 0x56);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x56);
		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0x56);
		ASSERT_EQ(memory[0x1F7], 0x56);

		PC = si.pc();

		ASSERT_EQ(PC, 3);
	}

	TEST_F(StandardInstructionTest, indirectYxor)
	{
		registerMap["A"] = 0x4A;
		registerMap["Y"] = 0xFF;

		memory[0xBB] = 0x01;
		memory[0xBC] = 0x03;

		memory[0x400] = 0xAC;


		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iEor),
			InstructionAddressingMode::yIndirect,
			PC,
			0xBB
		);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 5);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x400);
		ASSERT_EQ(si.getDecodeVal(), 0xAC);

		ASSERT_EQ(si.getCycles(), 6);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xAC ^ 0x4A);
		ASSERT_EQ(registerMap["SR"], 0x80);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0xAC ^ 0x4A);

		PC = si.pc();

		ASSERT_EQ(PC, 2);
	}

	TEST_F(StandardInstructionTest, xZPGSUB)
	{
		registerMap["SR"] = 0x9;
		registerMap["A"] = 0x74;
		registerMap["X"] = 0xAA;

		memory[0xE] = 0x99;

		Byte result = 0x75;

		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iSbc),
			InstructionAddressingMode::xZeroPage ,
			PC,
			0x64
		);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 4);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0xE);
		ASSERT_EQ(si.getDecodeVal(), 0x99);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x75);
		ASSERT_EQ(registerMap["SR"], 0x48);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0x75);

		PC = si.pc();

		ASSERT_EQ(PC, 2);
	}

	TEST_F(StandardInstructionTest, absYADD)
	{
		registerMap["SR"] = 0x8;
		registerMap["A"] = 0x1;
		registerMap["Y"] = 0x36;

		memory[0x57A] = 0x99;

		Byte result = 0x75;

		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iAdc),
			InstructionAddressingMode::absoluteY,
			PC,
			0x44,
			0x5
		);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 4);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x57A);
		ASSERT_EQ(si.getDecodeVal(), 0x99);

		ASSERT_EQ(si.getCycles(), 4);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x4B);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0x00);

		PC = si.pc();

		ASSERT_EQ(PC, 3);
	}

	TEST_F(StandardInstructionTest, absXCMP)
	{
		registerMap["SR"] = 0x0;
		registerMap["A"] = 0x1;
		registerMap["X"] = 0xBC;

		memory[0x600] = 0x1;

		Byte result = 0x75;

		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iCmp),
			InstructionAddressingMode::absoluteX,
			PC,
			0x44,
			0x5
		);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 4);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x600);
		ASSERT_EQ(si.getDecodeVal(), 0x1);

		ASSERT_EQ(si.getCycles(), 5);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x01);
		ASSERT_EQ(registerMap["SR"], 0x03);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0x01);

		PC = si.pc();

		ASSERT_EQ(PC, 3);
	}

	TEST_F(StandardInstructionTest, aASL)
	{
		registerMap["SR"] = 0x0;
		registerMap["A"] = 0x80;


		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iAsl),
			InstructionAddressingMode::immediate,
			PC
		);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x0);
		ASSERT_EQ(si.getDecodeVal(), 0x80);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x03);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["A"], 0x00);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(StandardInstructionTest, absRol)
	{
		registerMap["SR"] = 0x1;
		memory[0x1FFF] = 0x40;


		StandardInstruction si
		(
			static_cast<uint8_t>(StandardInstructions::iRol),
			InstructionAddressingMode::absolute,
			PC,
			0xFF,
			0x1F
		);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 6);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x1FFF);
		ASSERT_EQ(si.getDecodeVal(), 0x40);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x81);
		ASSERT_EQ(registerMap["SR"], 0x80);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory[0x1FFF], 0x81);

		PC = si.pc();

		ASSERT_EQ(PC, 3);
	}
}
