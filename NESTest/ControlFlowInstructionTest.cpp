#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class ControlFlowInstructionTest : public ::testing::Test {
	protected:

		ControlFlowInstructionTest() :
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

	TEST_F(ControlFlowInstructionTest, ClcTest)
	{
		registerMap["SR"] = 0x01;

		ControlFlowInstruction si
		(
			0,
			6,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iClc);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x0);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, SecTest)
	{
		registerMap["SR"] = 0x00;

		ControlFlowInstruction si
		(
			1,
			6,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iSec);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x01);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, CliTest)
	{
		registerMap["SR"] = 0x04;

		ControlFlowInstruction si
		(
			2,
			6,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iCli);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x00);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, SeiTest)
	{
		registerMap["SR"] = 0x00;

		ControlFlowInstruction si
		(
			3,
			6,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iSei);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);
		ASSERT_EQ(registerMap["SR"], 0x04);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, BrkTest)
	{
		PC = 0xABCD;
		registerMap["SR"] = 0xDF;

		registerMap["SP"] = 0xFF;

		memory.writeWord(IRQ_VECTOR, 0x1234);

		ControlFlowInstruction si
		(
			0,
			0,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iBrk);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 7);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xFF - 3);
		ASSERT_EQ(registerMap["SR"], 0xDF);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory.readWord(0x1FF - 2), 0xABCE); //PUSH PC + 1
		ASSERT_EQ(memory[0x1FF - 3], 0xDF); // PUSH SR
		ASSERT_EQ(registerMap["SP"], 0xFF - 3); // Implied 1

		PC = si.pc();

		ASSERT_EQ(PC, 0x1234);
	}

	TEST_F(ControlFlowInstructionTest, JsrTest)
	{
		PC = 0xBC45;

		registerMap["SP"] = 0xFF;

		ControlFlowInstruction si
		(
			1,
			0,
			0,
			PC,
			0x55,
			0x66
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iJsr);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::absolute);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 6);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x6655);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xFF - 2);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory.readWord(0x1FF - 2), 0xBC47); //PUSH PC + 1
		ASSERT_EQ(registerMap["SP"], 0xFF - 2); // Implied 1

		PC = si.pc();

		ASSERT_EQ(PC, 0x6655);
	}

	TEST_F(ControlFlowInstructionTest, RtiTest)
	{
		memory.writeWord(0x1FF - 2, 0x7865);
		memory[0x1FF - 3] = 0x54;

		registerMap["SP"] = 0xFC;

		PC = 0x3232;

		ControlFlowInstruction si
		(
			2,
			0,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iRti);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 6);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xFF);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["SR"], 0x54);
		ASSERT_EQ(registerMap["SP"], 0xFF); 

		PC = si.pc();

		ASSERT_EQ(PC, 0x7865 + 1);
	}

	TEST_F(ControlFlowInstructionTest, RtsTest)
	{
		memory.writeWord(0x1FF - 2, 0x7864);

		registerMap["SP"] = 0xFD;

		PC = 0x3123;

		ControlFlowInstruction si
		(
			3,
			0,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iRts);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 6);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xFF);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap["SP"], 0xFF);

		PC = si.pc();

		ASSERT_EQ(PC, 0x7864 + 1);
	}

}
