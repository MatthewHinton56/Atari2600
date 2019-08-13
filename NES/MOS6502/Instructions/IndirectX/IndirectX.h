#pragma once
#include "../Instruction.h"
#include "IndirectXConstants.h"

namespace mos6502
{
	class IndirectX : public Instruction
	{
	public:

		IndirectX
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
		InstructionOpcodeIndirectX getInstruction() const { return instruction; }
		InstructionTypeIndirectX getType() const { return type; }
		InstructionGroups getGroup() const { return group; }
		Byte getLowAddressByte() const { return lowAddressByte; }
		Byte getHighAddressByte() const { return highAddressByte; }
		Word getAddress() const { return address; }
		Byte getData() const { return data; }
		Byte getPointer() const { return pointer; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeIndirectX instruction;
		InstructionTypeIndirectX type;
		InstructionGroups group;
		Byte lowAddressByte;
		Byte highAddressByte;
		Word address;
		Byte data;
		Byte reg;
		Byte regIndex;
		Byte pointer;

	};
}