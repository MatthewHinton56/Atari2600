#pragma once
#include "../Instruction.h"
#include "ZeropageIndexedConstants.h"

namespace mos6502
{
	class ZeropageIndexed
	{
	public:

		ZeropageIndexed
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
		InstructionOpcodeZeropageIndexed getInstruction() const { return instruction; }
		InstructionTypeZeropageIndexed getType() const { return type; }
		InstructionGroups getGroup() const { return group; }
		Byte getLowAddressByte() const { return lowAddressByte; }
		Word getAddress() const { return address; }
		Byte getData() const { return data; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeZeropageIndexed instruction;
		InstructionTypeZeropageIndexed type;
		InstructionGroups group;
		Byte lowAddressByte;
		Word address;
		Byte data;
		Byte reg;
		Byte regIndex;
	};
}