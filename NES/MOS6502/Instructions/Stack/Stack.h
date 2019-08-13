#pragma once
#include "../Instruction.h"
#include "StackConstants.h"

namespace mos6502
{
	class Stack
	{
	public:

		Stack
		(
			Byte opcode
		);

		virtual int32_t step
		(
			Word& PC,
			RegisterMap& registerMap, 
			Memory<PAGE_SIZE, NUM_PAGES>& mem
		);

		int32_t getStepCount() const { return stepCount; }
		Byte getOpcode() const { return opcode; }
		InstructionOpcodeStack getInstruction() const { return instruction; }
		InstructionTypeStack getType() const { return type; }
		InstructionGroups getGroup() const { return group; }
		Byte getLowAddressByte() const { return lowAddressByte; }
		Byte getLatch() const { return latch; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeStack instruction;
		InstructionTypeStack type;
		InstructionGroups group;
		Byte lowAddressByte;
		Byte reg;
		Byte latch;
	};
}