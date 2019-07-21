#pragma once

#include "pch.h"

#define COMMA ,

using namespace mos6507;

namespace {

	class OperationTest : public ::testing::Test {
	protected:

		OperationTest()
			:
			statusRegister(0)
		{}

		void SetUp() override
		{
			statusRegister = 0;
		}

		Byte statusRegister;
	};

	TEST_F(OperationTest, BCDConvert)
	{
		ASSERT_EQ(convertByteToBCD(0x99), 99);
		ASSERT_EQ(convertByteToBCD(0x47), 47);
		ASSERT_EQ(convertBCDTOByte(99), 0x99);
		ASSERT_EQ(convertBCDTOByte(47), 0x47);
	}

	TEST_F(OperationTest, BCDAdditon)
	{
		ASSERT_EQ(addWithCarryBCD(0x01, 0x99, statusRegister), 0x00);
		ASSERT_EQ(statusRegister, 0x43);

		statusRegister = 0x1;
		ASSERT_EQ(addWithCarryBCD(0x00, 0x99, statusRegister), 0x00);
		ASSERT_EQ(statusRegister, 0x43);

		statusRegister = 0x0;
		ASSERT_EQ(addWithCarryBCD(0x04, 0x94, statusRegister), 0x98);
		ASSERT_EQ(statusRegister, 0xC0);

		statusRegister = 0x1;
		ASSERT_EQ(addWithCarryBCD(0x04, 0x94, statusRegister), 0x99);
		ASSERT_EQ(statusRegister, 0xC0);

		statusRegister = 0x0;
		ASSERT_EQ(addWithCarryBCD(0x14, 0x94, statusRegister), 0x08);
		ASSERT_EQ(statusRegister, 0x41);

		statusRegister = 0x1;
		ASSERT_EQ(addWithCarryBCD(0x14, 0x94, statusRegister), 0x09);
		ASSERT_EQ(statusRegister, 0x41);

		statusRegister = 0x0;
		ASSERT_EQ(addWithCarryBCD(0x14, 0x04, statusRegister), 0x18);
		ASSERT_EQ(statusRegister, 0x40);

		statusRegister = 0x1;
		ASSERT_EQ(addWithCarryBCD(0x14, 0x04, statusRegister), 0x19);
		ASSERT_EQ(statusRegister, 0x40);

		statusRegister = 0xFE;
		ASSERT_EQ(addWithCarryBCD(0x14, 0x04, statusRegister), 0x18);
		ASSERT_EQ(statusRegister, 0x7C);

		statusRegister = 0xFF;
		ASSERT_EQ(addWithCarryBCD(0x14, 0x04, statusRegister), 0x19);
		ASSERT_EQ(statusRegister, 0x7C);
	}

	TEST_F(OperationTest, BCDSubstruction)
	{
		ASSERT_EQ(false, true);
	}

	TEST_F(OperationTest, BinaryAddition)
	{
		ASSERT_EQ(false, true);
	}

	TEST_F(OperationTest, BinarySubtraction)
	{
		ASSERT_EQ(false, true);
	}

	TEST_F(OperationTest, BinaryLogic)
	{
		ASSERT_EQ(false, true);
	}

	TEST_F(OperationTest, BinaryShift)
	{
		ASSERT_EQ(false, true);
	}

}



