#pragma once
#include "../../MemoryAccessor.h"
#include "../../mos6502Constants.h"
#include "../Instruction.h"
#include "StandardInstructionConstants.h"

namespace mos6502
{
	class StandardInstruction : public Instruction
	{
	public:

		StandardInstruction
		(
			uint8_t aValue,
			uint8_t bValue,
			uint8_t cValue,
			Word PC,
			Byte lowOrderOperand = 0,
			Byte highOrderOperand = 0
		);

		virtual ~StandardInstruction() = default;

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

		virtual StandardInstructions getInstruction() const;

		virtual InstructionAddressingMode getDecodeMode() const;

		virtual Instructions getInstructionType() const;

	protected:

		StandardInstructions instruction;
		InstructionAddressingMode decodeMode;

		Byte lowOrderOperand;
		Byte highOrderOperand;

		Byte decodeVal;
		Word address;
		Byte executeVal;
		Byte memoryVal;
		Word PC;
		unsigned int instructionSize;
	};
}
