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

	//All Decode Tests will Use And,
	//Special Mode will Use ASL

	TEST_F(StandardInstructionTest, XIndirectTest)
	{
		memory[0x00] = 0x01;
		memory[0x01] = 0x02;
		memory[0x201] = 0xCA;
		registerMap["X"] = 0x80;
		registerMap["A"] = 0xFF;
		
		StandardInstruction si
		(
			9,
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

}
