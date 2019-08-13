#pragma once
#include "../Instruction.h"
#include "AccumulatorConstants.h"

namespace mos6502
{
	class Accumulator
	{
	public:

		Accumulator
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
		InstructionOpcodeAccumulator getInstruction() const { return instruction; }
		InstructionTypeAccumulator getType() const { return type; }
		InstructionGroups getGroup() const { return group; }

	private:

		int32_t stepCount;

		Byte opcode;
		InstructionOpcodeAccumulator instruction;
		InstructionTypeAccumulator type;
		InstructionGroups group;

	};
}