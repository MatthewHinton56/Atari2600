#pragma once
#include "../MemoryAccessor.h"
#include "../MOS6507Constants.h"
#include "Instruction.h"
#include "StandardInstructionConstants.h"

namespace mos6507
{
	class StandardInstruction : Instruction
	{
	public:

		StandardInstruction
		(
			uint8_t caValue,
			InstructionAddressingMode decodeMode,
			Word PC,
			Byte lowOrderOperand = 0,
			Byte highOrderOperand = 0
		);


		virtual void decode
		(
			RegisterMap& registerMap, 
			MemoryAccessor& memory
		);

		virtual void execute(RegisterMap registerMap);

		virtual void writeBack(MemoryAccessor& memory, RegisterMap& registerMap);

		virtual Word pc();

		virtual Byte getDecodeVal() const;

		virtual Byte getExceuteVal() const;

		virtual Byte getMemoryVal() const;

		virtual Byte getPC() const;

		virtual Byte getInstructionSize() const;

		virtual Byte getCycles() const;

	protected:

		StandardInstructions instruction;
		InstructionAddressingMode decodeMode;
		bool specialMode;

		Byte lowOrderOperand;
		Byte highOrderOperand;

		Byte decodeVal;
		Word address;
		Byte executeVal;
		Byte memoryVal;
		Word PC;
		unsigned int instructionSize;
		unsigned int cycles;
	};
}
