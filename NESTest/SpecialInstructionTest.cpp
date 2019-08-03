#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class SpecialInstructionTest : public ::testing::Test {
	protected:

		SpecialInstructionTest() :
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

	TEST_F(SpecialInstructionTest, BrkNmiTest)
	{
		PC = 0xABCD;
		registerMap[SR] = 0x81;

		registerMap[SP] = 0xFF;

		memory.writeWord(NMI_VECTOR, 0x1234);

		SpecialInstruction si
		(
			SpecialInstructions::iBrkNmi,
			PC
		);

		ASSERT_EQ(si.getInstruction(), SpecialInstructions::iBrkNmi);
		ASSERT_EQ(si.getDecodeMode(), SpecialInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 0);

		ASSERT_EQ(si.getCycles(), 7);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xFF - 3);
		ASSERT_EQ(registerMap[SR], 0x81);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory.readWord(0x1FF - 2), 0xABCD); //PUSH PC
		ASSERT_EQ(memory[0x1FF - 3], 0x81); // PUSH SR
		ASSERT_EQ(registerMap[SP], 0xFF - 3); // Implied 1

		ASSERT_EQ(registerMap[SR], 0x85); // Implied 1

		PC = si.pc();

		ASSERT_EQ(PC, 0x1234);
	}


	TEST_F(SpecialInstructionTest, BrkIrqTest)
	{
		PC = 0xABCD;
		registerMap[SR] = 0x81;

		registerMap[SP] = 0xFF;

		memory.writeWord(IRQ_VECTOR, 0x1234);

		SpecialInstruction si
		(
			SpecialInstructions::iBrkIrq,
			PC
		);

		ASSERT_EQ(si.getInstruction(), SpecialInstructions::iBrkIrq);
		ASSERT_EQ(si.getDecodeMode(), SpecialInstructionAddressingMode::implied);

		ASSERT_EQ(si.getInstructionSize(), 0);

		ASSERT_EQ(si.getCycles(), 7);

		si.decode(registerMap, memory);
		ASSERT_EQ(si.getAddress(), 0);
		ASSERT_EQ(si.getDecodeVal(), 0x0);

		si.execute(registerMap);

		ASSERT_EQ(si.getExceuteVal(), 0xFF - 3);
		ASSERT_EQ(registerMap[SR], 0x81);

		si.writeBack(registerMap, memory);

		ASSERT_EQ(memory.readWord(0x1FF - 2), 0xABCD); //PUSH PC
		ASSERT_EQ(memory[0x1FF - 3], 0x81); // PUSH SR
		ASSERT_EQ(registerMap[SP], 0xFF - 3); // Implied 1

		ASSERT_EQ(registerMap[SR], 0x85); // Implied 1

		PC = si.pc();

		ASSERT_EQ(PC, 0x1234);
	}

}
