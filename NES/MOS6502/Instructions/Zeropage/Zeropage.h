#pragma once
#include "../Instruction.h"
#include "ZeropageConstants.h"

namespace mos6502
{
	class Zeropage : public Instruction
	{
	public:

		Zeropage
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
		InstructionOpcodeZeropage getInstruction() const { return instruction; }
		InstructionTypeZeropage getType() const { return type; }
		InstructionGroups getGroup() const { return group; }
		Byte getLowAddressByte() const { return lowAddressByte; }
		Byte getAddress() const { return address; }
		Byte getData() const { return data; }
		Byte getReg() const { return reg; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeZeropage instruction;
		InstructionTypeZeropage type;
		InstructionGroups group;
		Byte lowAddressByte;
		Byte address;
		Byte data;
		Byte reg;
	};
}