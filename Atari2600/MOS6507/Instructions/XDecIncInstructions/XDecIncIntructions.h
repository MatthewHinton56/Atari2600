#pragma once
#pragma once
#include "../../MemoryAccessor.h"
#include "../../MOS6507Constants.h"
#include "../Instruction.h"
#include "XDecIncInstructionConstants.h"

namespace mos6507
{
	class XDecIncInstruction : Instruction
	{
	public:

		XDecIncInstruction
		(
			uint8_t caValue,
			uint8_t bValue,
			Word PC,
			Byte lowOrderOperand = 0,
			Byte highOrderOperand = 0
		);


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

	protected:

		XDecIncInstructions instruction;
		InstructionAddressingMode decodeMode;

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
