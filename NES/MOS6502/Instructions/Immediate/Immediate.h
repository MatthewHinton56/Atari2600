#pragma once
#include "../Instruction.h"
#include "ImmediateConstants.h"

namespace mos6502
{
	class Immediate
	{
	public:

		Immediate
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
		InstructionOpcodeImmediate getInstruction() const { return instruction; }
		InstructionTypeImmediate getType() const { return type; }
		InstructionGroups getGroup() const { return group; }
		Byte getLowAddressByte() const { return lowAddressByte; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeImmediate instruction;
		InstructionTypeImmediate type;
		InstructionGroups group;
		Byte lowAddressByte;
		Byte reg;

	};
}