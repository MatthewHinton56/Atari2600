#pragma once
#include "../Instruction.h"
#include "AbsoluteIndexedConstants.h"

namespace mos6502
{
	class AbsoluteIndexed
	{
	public:

		AbsoluteIndexed
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
		InstructionOpcodeAbsoluteIndexed getInstrucion() const { return instruction; }
		InstructionTypeAbsoluteIndexed getType() const { return type; }
		InstructionGroups getGroup() const { return group; }
		Byte getLowAddressByte() const { return lowAddressByte; }
		Byte getHighAddressByte() const { return highAddressByte; }
		Word getAddress() const { return address; }
		Byte getData() const { return data; }
		Byte getReg() const { return reg; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeAbsoluteIndexed instruction;
		InstructionTypeAbsoluteIndexed type;
		InstructionGroups group;
		Byte lowAddressByte;
		Byte highAddressByte;
		Word address;
		Byte data;
		Byte reg;
		Byte regIndex;

		bool pageBoundaryCrossed;
	};
}