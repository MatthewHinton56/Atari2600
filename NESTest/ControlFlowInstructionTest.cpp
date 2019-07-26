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

}