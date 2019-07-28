#pragma once
#pragma once
#include "../../MemoryAccessor.h"
#include "../../mos6502Constants.h"
#include "../Instruction.h"
#include "SpecialInstructionConstants.h"

namespace mos6502
{
	class SpecialInstruction : public Instruction
	{
	public:

		SpecialInstruction
		(
			SpecialInstructions instruction,
			Word PC
		);

		virtual ~SpecialInstruction() = default;

		virtual void decode
		(
			RegisterMap& registerMap,
			MemoryAccessor& memory
		);

		virtual void execute(RegisterMap& registerMap);

		virtual void writeBack(RegisterMap& registerMap, MemoryAccessor& memory);

		virtual Word pc();

		virtual Byte getDecodeVal() const;

		virtual Word getAddress() const;

		virtual Byte getExceuteVal() const;

		virtual Byte getMemoryVal() const;

		virtual Word getPC() const;

		virtual unsigned int getInstructionSize() const;

		virtual unsigned int getCycles() const;

		virtual SpecialInstructions getInstruction() const;

		virtual SpecialInstructionAddressingMode getDecodeMode() const;

		virtual Instructions getInstructionType() const;

	protected:

		SpecialInstructions instruction;
		SpecialInstructionAddressingMode decodeMode;

		Word newPC;
		Word PC;

		Byte lowOrderOperand;
		Byte highOrderOperand;

		Byte decodeVal;
		Word address;
		Byte executeVal;
		Byte memoryVal;

		unsigned int instructionSize;

		Byte branch;
	};
}
