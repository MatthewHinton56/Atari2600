#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class ControlFlowInstructionTest : public ::testing::Test {
	protected:

		ControlFlowInstructionTest() :
			mem(),
			memory(mem),
			registerMap(),
			PC(0)
		{}


		void SetUp() override
		{
			registerMap[AC] = 0;
			registerMap[X] = 0;
			registerMap[Y] = 0;
			registerMap[SR] = 0;
			registerMap[SP] = 0;
		}
		Memory<PAGE_SIZE, NUM_PAGES> mem;
		MemoryAccessor memory;
		RegisterMap registerMap;
		Word PC;
	};

	TEST_F(ControlFlowInstructionTest, ClcTest)
	{
		registerMap[SR] = 0x01;

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
		ASSERT_EQ(registerMap[SR], 0x0);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, SecTest)
	{
		registerMap[SR] = 0x00;

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
		ASSERT_EQ(registerMap[SR], 0x01);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, CliTest)
	{
		registerMap[SR] = 0x04;

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
		ASSERT_EQ(registerMap[SR], 0x00);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, SeiTest)
	{
		registerMap[SR] = 0x00;

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
		ASSERT_EQ(registerMap[SR], 0x04);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, BrkTest)
	{
		PC = 0xABCD;
		registerMap[SR] = 0x81;

		registerMap[SP] = 0xFF;

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
		ASSERT_EQ(registerMap[SR], 0x81);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory.readWord(0x1FF - 2), 0xABCE); //PUSH PC + 1
		ASSERT_EQ(memory[0x1FF - 3], 0x81); // PUSH SR
		ASSERT_EQ(registerMap[SP], 0xFF - 3); // Implied 1

		ASSERT_EQ(registerMap[SR], 0x95); // Implied 1

		PC = si.pc();

		ASSERT_EQ(PC, 0x1234);
	}

	TEST_F(ControlFlowInstructionTest, JsrTest)
	{
		PC = 0xBC45;

		registerMap[SP] = 0xFF;

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
		ASSERT_EQ(registerMap[SP], 0xFF - 2); // Implied 1

		PC = si.pc();

		ASSERT_EQ(PC, 0x6655);
	}

	TEST_F(ControlFlowInstructionTest, RtiTest)
	{
		memory.writeWord(0x1FF - 2, 0x7865);
		memory[0x1FF - 3] = 0x54;

		registerMap[SP] = 0xFC;

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

		ASSERT_EQ(registerMap[SR], 0x54);
		ASSERT_EQ(registerMap[SP], 0xFF); 

		PC = si.pc();

		ASSERT_EQ(PC, 0x7865 + 1);
	}

	TEST_F(ControlFlowInstructionTest, RtsTest)
	{
		memory.writeWord(0x1FF - 2, 0x7864);

		registerMap[SP] = 0xFD;

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

		ASSERT_EQ(registerMap[SP], 0xFF);

		PC = si.pc();

		ASSERT_EQ(PC, 0x7864 + 1);
	}

	TEST_F(ControlFlowInstructionTest, BitAbsTest)
	{
		memory[0x1234] = 0x40;

		ControlFlowInstruction si
		(
			1,
			3,
			0,
			PC,
			0x34,
			0x12
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iBit);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::absolute);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 4);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x1234);
		ASSERT_EQ(si.getDecodeVal(), 0x40);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap[SR], 0x42);

		PC = si.pc();

		ASSERT_EQ(PC, 3);
	}

	TEST_F(ControlFlowInstructionTest, BitZpgTest)
	{
		memory[0x34] = 0x80;
		registerMap[AC] = 0x80;
		ControlFlowInstruction si
		(
			1,
			1,
			0,
			PC,
			0x34
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iBit);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::zeroPage);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 3);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x34);
		ASSERT_EQ(si.getDecodeVal(), 0x80);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap[SR], 0x80);

		PC = si.pc();

		ASSERT_EQ(PC, 2);
	}

	TEST_F(ControlFlowInstructionTest, JmpAbsTest)
	{
		ControlFlowInstruction si
		(
			2,
			3,
			0,
			PC,
			0x43,
			0x78
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iJmp);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::absolute);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 3);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x7843);
		ASSERT_EQ(si.getDecodeVal(), 0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 0x7843);
	}

	TEST_F(ControlFlowInstructionTest, JmpZpgTest)
	{
		memory[0x5555] = 0x11;
		memory[0x5556] = 0x22;
		ControlFlowInstruction si
		(
			3,
			3,
			0,
			PC,
			0x55,
			0x55
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iJmp);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::indirect);

		ASSERT_EQ(si.getInstructionSize(), 3);

		ASSERT_EQ(si.getCycles(), 5);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0x2211);
		ASSERT_EQ(si.getDecodeVal(), 0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x00);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(PC, 0x2211);
	}

	TEST_F(ControlFlowInstructionTest, PhpTest)
	{
		registerMap[SR] = 0x43;
		registerMap[SP] = 0x66;
 		ControlFlowInstruction si
		(
			0,
			2,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iPhp);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 3);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x43);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x65);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory[0x165], 0x43);
		ASSERT_EQ(registerMap[SP], 0x65);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, PhaTest)
	{
		registerMap[AC] = 0xEE;
		registerMap[SP] = 0x23;
		ControlFlowInstruction si
		(
			2,
			2,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iPha);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 3);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0xEE);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x22);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory[0x122], 0xEE);
		ASSERT_EQ(registerMap[SP], 0x22);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, PlaTest)
	{
		registerMap[AC] = 0xEE;
		registerMap[SP] = 0x23;
		memory[0x123] = 0x76;
		ControlFlowInstruction si
		(
			3,
			2,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iPla);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 4);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x76);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x24);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap[AC], 0x76);
		ASSERT_EQ(registerMap[SP], 0x24);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, PlpTest)
	{
		registerMap[AC] = 0xEE;
		registerMap[SP] = 0x23;
		memory[0x123] = 0x76;
		ControlFlowInstruction si
		(
			1,
			2,
			0,
			PC
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iPlp);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 1);

		ASSERT_EQ(si.getCycles(), 4);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x76);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x24);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(registerMap[SR], 0x76);
		ASSERT_EQ(registerMap[SP], 0x24);

		PC = si.pc();

		ASSERT_EQ(PC, 1);
	}

	TEST_F(ControlFlowInstructionTest, BplTest)
	{
		registerMap[SR] = 0x00;
		PC = 0x100;
		ControlFlowInstruction si
		(
			0,
			4,
			0,
			PC,
			0x80
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iBpl);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::relative);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x80);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x80);
		ASSERT_EQ(registerMap[SR], 0x00);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(si.getCycles(), 4);

		ASSERT_EQ(PC, 0x82);
	}

	TEST_F(ControlFlowInstructionTest, BmiTest)
	{
		registerMap[SR] = 0x00;
		PC = 0x100;
		ControlFlowInstruction si
		(
			1,
			4,
			0,
			PC,
			0x80
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iBmi);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::relative);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x80);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0);
		ASSERT_EQ(registerMap[SR], 0x00);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(si.getCycles(), 2);

		ASSERT_EQ(PC, 0x102);
	}

	TEST_F(ControlFlowInstructionTest, BvcTest)
	{
		registerMap[SR] = 0x00;
		PC = 0x100;
		ControlFlowInstruction si
		(
			2,
			4,
			0,
			PC,
			0x10
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iBvc);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::relative);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x10);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x10);
		ASSERT_EQ(registerMap[SR], 0x00);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(si.getCycles(), 3);

		ASSERT_EQ(PC, 0x112);
	}

	TEST_F(ControlFlowInstructionTest, BvsTest)
	{
		registerMap[SR] = 0x40;
		PC = 0x1FD;
		ControlFlowInstruction si
		(
			3,
			4,
			0,
			PC,
			0x7F
		);

		ASSERT_EQ(si.getInstruction(), ControlFlowInstructions::iBvs);
		ASSERT_EQ(si.getDecodeMode(), ControlFlowInstructionAddressingMode::relative);

		ASSERT_EQ(si.getInstructionSize(), 2);

		ASSERT_EQ(si.getCycles(), 2);

		si.decode(registerMap, memory);

		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x7F);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0x7F);
		ASSERT_EQ(registerMap[SR], 0x40);

		si.writeBack(registerMap, memory);

		PC = si.pc();

		ASSERT_EQ(si.getCycles(), 4);

		ASSERT_EQ(PC, 0x27E);
	}

}
