#pragma once
#include "../Instruction.h"
#include "indirectXConstants.h"

namespace mos6502
{
	class indirectX
	{
	public:

		indirectX
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
		InstructionOpcodeindirectX getInstrucion() const { return instruction; }
		InstructionTypeindirectX getType() const { return type; }
		InstructionGroups getGroup() const { return group; }
		Byte getLowAddressByte() const { return lowAddressByte; }
		Byte getHighAddressByte() const { return highAddressByte; }
		Word getAddress() const { return address; }
		Byte getData() const { return data; }
		Byte getPointer() const { return pointer; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeindirectX instruction;
		InstructionTypeindirectX type;
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