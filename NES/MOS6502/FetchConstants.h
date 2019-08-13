#pragma once

#include "MOS6502Constants.h"
#include "Instructions/InstructionConstants.h"
#include "Instructions\Absolute\Absolute.h"
#include "Instructions\Zeropage\Zeropage.h"
#include "Instructions\ZeropageIndexed\ZeropageIndexed.h"
#include "Instructions\AbsoluteIndexed\AbsoluteIndexed.h"
#include "Instructions\IndirectY\IndirectY.h"
#include "Instructions\IndirectX\IndirectX.h"
#include "Instructions\Indirect\Indirect.h"
#include "Instructions\Relative\Relative.h"
#include "Instructions\Immediate\Immediate.h"
#include "Instructions\Accumulator\Accumulator.h"
#include "Instructions\Implied\Implied.h"
#include "Instructions\Stack\Stack.h"
#include "Instructions\Special\Special.h"
#include <cstdint>
#include <unordered_set>

namespace mos6502
{
	static const Byte INDIRECT_JMP = 0x6C;
	static const Byte INDIRECT_Y_BC = 0x11;
	static const Byte RELATIVE_BC = 0x10;
	static const Byte INDIRECT_X_BC = 0x01;

	static std::unordered_set<Byte> ACCUMULATOR_INSTRUCTIONS
	{
		static_cast<Byte>(InstructionOpcodeAccumulator::iAsl),
		static_cast<Byte>(InstructionOpcodeAccumulator::iRol),
		static_cast<Byte>(InstructionOpcodeAccumulator::iLsr),
		static_cast<Byte>(InstructionOpcodeAccumulator::iRor)
	};

	static std::unordered_set<Byte> IMMEDIATE_INSTRUCTIONS
	{
		static_cast<Byte>(InstructionOpcodeImmediate::iLdy),
		static_cast<Byte>(InstructionOpcodeImmediate::iCpy),
		static_cast<Byte>(InstructionOpcodeImmediate::iCpx),
		static_cast<Byte>(InstructionOpcodeImmediate::iOra),
		static_cast<Byte>(InstructionOpcodeImmediate::iAnd),
		static_cast<Byte>(InstructionOpcodeImmediate::iEor),
		static_cast<Byte>(InstructionOpcodeImmediate::iAdc),
		static_cast<Byte>(InstructionOpcodeImmediate::iLda),
		static_cast<Byte>(InstructionOpcodeImmediate::iCmp),
		static_cast<Byte>(InstructionOpcodeImmediate::iSbc),
		static_cast<Byte>(InstructionOpcodeImmediate::iLdx)
	};

	static std::unordered_set<Byte> IMPLIED_INSTRUCTIONS
	{
		static_cast<Byte>(InstructionOpcodeImplied::iDey),
		static_cast<Byte>(InstructionOpcodeImplied::iTay),
		static_cast<Byte>(InstructionOpcodeImplied::iIny),
		static_cast<Byte>(InstructionOpcodeImplied::iInx),
		static_cast<Byte>(InstructionOpcodeImplied::iTxa),
		static_cast<Byte>(InstructionOpcodeImplied::iTax),
		static_cast<Byte>(InstructionOpcodeImplied::iDex),
		static_cast<Byte>(InstructionOpcodeImplied::iNop),
		static_cast<Byte>(InstructionOpcodeImplied::iClc),
		static_cast<Byte>(InstructionOpcodeImplied::iSec),
		static_cast<Byte>(InstructionOpcodeImplied::iCli),
		static_cast<Byte>(InstructionOpcodeImplied::iSei),
		static_cast<Byte>(InstructionOpcodeImplied::iTya),
		static_cast<Byte>(InstructionOpcodeImplied::iClv),
		static_cast<Byte>(InstructionOpcodeImplied::iCld),
		static_cast<Byte>(InstructionOpcodeImplied::iSed),
		static_cast<Byte>(InstructionOpcodeImplied::iTxs),
		static_cast<Byte>(InstructionOpcodeImplied::iTsx)
	};

	static std::unordered_set<Byte> STACK_INSTRUCTIONS
	{
		static_cast<Byte>(InstructionOpcodeStack::iBrk),
		static_cast<Byte>(InstructionOpcodeStack::iJsr),
		static_cast<Byte>(InstructionOpcodeStack::iRti),
		static_cast<Byte>(InstructionOpcodeStack::iRts),
		static_cast<Byte>(InstructionOpcodeStack::iPhp),
		static_cast<Byte>(InstructionOpcodeStack::iPlp),
		static_cast<Byte>(InstructionOpcodeStack::iPha),
		static_cast<Byte>(InstructionOpcodeStack::iPla)
	};
}