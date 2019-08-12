#pragma once
#include "../Instruction.h"

namespace mos6502
{
	class Indirect
	{
	public:

		Indirect
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
		InstructionGroups getGroup() const { return group; }
		Byte getLowAddressByte() const { return lowAddressByte; }
		Byte getHighAddressByte() const { return highAddressByte; }
		Word getAddress() const { return address; }
		Byte getData() const { return data; }
		Word getPointer() const { return pointer; }
		Byte getLatch() const { return latch; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionGroups group;
		Byte lowAddressByte;
		Byte highAddressByte;
		Word address;
		Byte data;
		Word pointer;
		Byte latch;

	};
}