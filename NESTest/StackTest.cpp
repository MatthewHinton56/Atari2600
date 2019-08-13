
#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class StackTest : public ::testing::Test {
	protected:

		StackTest() :
			PC(),
			mem(),
			registerMap()
		{}


		void SetUp() override
		{
		}

		Word PC;
		Memory<PAGE_SIZE, NUM_PAGES> mem;
		RegisterMap registerMap;
	};

	TEST_F(StackTest, stackBrk)
	{
		PC = 0x3333;
		registerMap[SP] = 0xFF;
		registerMap[SR] = 0xC3;
		mem.writeByte(IRQ_VECTOR, 0x11);
		mem.writeByte(IRQ_VECTOR + 1, 0x12);

		Stack instr(0x00);
		PC++;
		ASSERT_EQ(instr.getOpcode(), 0x00);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeStack::iBrk);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::brk);
		ASSERT_EQ(PC, 0x3334);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(PC, 0x3335);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0x33);
		ASSERT_EQ(registerMap[SP], 0xFE);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0x35);
		ASSERT_EQ(registerMap[SP], 0xFD);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0xD3);
		ASSERT_EQ(registerMap[SP], 0xFC);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(instr.getLatch(), 0x11);
		ASSERT_EQ(registerMap[SR], 0xC7);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 7);
		ASSERT_EQ(PC, 0x1211);
	}

	TEST_F(StackTest, stackJsr)
	{
		PC = 0x3333;
		registerMap[SP] = 0xFF;
		mem.writeByte(0x3334, 0x11);
		mem.writeByte(0x3335, 0x12);

		Stack instr(0x20);
		PC++;
		ASSERT_EQ(instr.getOpcode(), 0x20);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeStack::iJsr);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::jsr);
		ASSERT_EQ(PC, 0x3334);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);
		ASSERT_EQ(instr.getLowAddressByte(), 0x11);
		ASSERT_EQ(PC, 0x3335);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0x33);
		ASSERT_EQ(registerMap[SP], 0xFE);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0x35);
		ASSERT_EQ(registerMap[SP], 0xFD);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(PC, 0x1211);
	}

	TEST_F(StackTest, stackRti)
	{
		PC = 0x3333;
		registerMap[SP] = 0xFC;
		registerMap[SR] = 0xAC;
		mem.writeByte(0x1FD, 0x53);
		mem.writeByte(0x1FE, 0x11);
		mem.writeByte(0x1FF, 0x12);

		Stack instr(0x40);
		PC++;
		ASSERT_EQ(instr.getOpcode(), 0x40);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeStack::iRti);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::rti);
		ASSERT_EQ(PC, 0x3334);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SP], 0xFD);


		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[SP], 0xFE);
		ASSERT_EQ(registerMap[SR], 0x43);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(registerMap[SP], 0xFF);
		ASSERT_EQ(instr.getLatch(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(PC, 0x1211);
	}

	TEST_F(StackTest, stackRts)
	{
		PC = 0x3333;
		registerMap[SP] = 0xFD;
		mem.writeByte(0x1FE, 0x11);
		mem.writeByte(0x1FF, 0x12);

		Stack instr(0x60);
		PC++;
		ASSERT_EQ(instr.getOpcode(), 0x60);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeStack::iRts);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::rts);
		ASSERT_EQ(PC, 0x3334);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SP], 0xFE);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[SP], 0xFF);
		ASSERT_EQ(instr.getLatch(), 0x11);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 5);
		ASSERT_EQ(PC, 0x1211);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 6);
		ASSERT_EQ(PC, 0x1212);
	}

	TEST_F(StackTest, stackPhp)
	{
		registerMap[SR] = 0x33;
		registerMap[SP] = 0xFD;
		Stack instr(0x08);
		PC++;
		ASSERT_EQ(instr.getOpcode(), 0x08);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeStack::iPhp);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ph);
		ASSERT_EQ(PC, 0x1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SP], 0xFC);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0x33);
	}

	TEST_F(StackTest, stackPlp)
	{
		registerMap[SR] = 0x33;
		registerMap[SP] = 0xFD;
		mem.writeByte(0x1FE, 0x11);
		Stack instr(0x28);
		PC++;
		ASSERT_EQ(instr.getOpcode(), 0x28);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeStack::iPlp);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::pl);
		ASSERT_EQ(PC, 0x1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SP], 0xFE);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[SR], 0x11);
	}

	TEST_F(StackTest, stackPha)
	{
		registerMap[AC] = 0x33;
		registerMap[SP] = 0xFD;
		Stack instr(0x48);
		PC++;
		ASSERT_EQ(instr.getOpcode(), 0x48);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeStack::iPha);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::ph);
		ASSERT_EQ(PC, 0x1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SP], 0xFC);
		ASSERT_EQ(mem.readByte(0x100 | (registerMap[SP] + 1)), 0x33);
	}

	TEST_F(StackTest, stackPla)
	{
		registerMap[AC] = 0x33;
		registerMap[SP] = 0xFD;
		mem.writeByte(0x1FE, 0x11);
		Stack instr(0x68);
		PC++;
		ASSERT_EQ(instr.getOpcode(), 0x68);
		ASSERT_EQ(instr.getInstruction(), InstructionOpcodeStack::iPla);
		ASSERT_EQ(instr.getGroup(), InstructionGroups::pl);
		ASSERT_EQ(PC, 0x1);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 2);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 0);
		ASSERT_EQ(instr.getStepCount(), 3);
		ASSERT_EQ(registerMap[SP], 0xFE);

		ASSERT_EQ(instr.step(PC, registerMap, mem), 1);
		ASSERT_EQ(instr.getStepCount(), 4);
		ASSERT_EQ(registerMap[AC], 0x11);
	}
}
