#pragma once

#include "pch.h"


#define COMMA ,

using namespace mos6507;

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
			static_cast<uint8_t>(XDecIncInstructions::iStx),
			static_cast<uint8_t>(InstructionAddressingMode::immediate),
			PC
		);

		ASSERT_EQ(si.getInstructionSize(), 1);

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

}
