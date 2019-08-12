#pragma once
#include "../Instruction.h"
#include "IndirectYConstants.h"

namespace mos6502
{
	class IndirectY
	{
	public:

		IndirectY
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
		InstructionOpcodeIndirectY getInstruction() const { return instruction; }
		InstructionTypeIndirectY getType() const { return type; }
		InstructionGroups getGroup() const { return group; }
		Byte getLowAddressByte() const { return lowAddressByte; }
		Byte getHighAddressByte() const { return highAddressByte; }
		Word getAddress() const { return address; }
		Byte getData() const { return data; }
		Byte getPointer() const { return pointer; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeIndirectY instruction;
		InstructionTypeIndirectY type;
		InstructionGroups group;
		Byte lowAddressByte;
		Byte highAddressByte;
		Word address;
		Byte data;
		Byte reg;
		Byte regIndex;
		Byte pointer;

		bool pageBoundaryCrossed;
	};
}