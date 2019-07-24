#pragma once
#include <map>

namespace mos6502
{
	enum class ControlFlowInstructionAddressingMode : uint8_t
	{
		zeroPage,
		implied,
		absolute,
		relative,
		indirect
	};

	enum class ControlFlowInstructions : uint8_t
	{
		iBrk,
		iPhp,
		iBpl,
		iClc,

		iJsr,
		iBit,
		iPlp,
		iBmi,
		iSec,

		iRti,
		iPha,
		iJmp,
		iBvc,
		iCli,

		iRts,
		iPla,
		iBvs,
		iSei
	};

	static std::map<uint8_t, ControlFlowInstructions> CFHexToInstructions
	{
		{0x00, ControlFlowInstructions::iBrk},
		{0x88, ControlFlowInstructions::iPhp},
		{0x10, ControlFlowInstructions::iBpl},
		{0x18, ControlFlowInstructions::iClc},

		{0x20, ControlFlowInstructions::iJsr},
		{0x24, ControlFlowInstructions::iBit},
		{0x28, ControlFlowInstructions::iPlp},
		{0x2C, ControlFlowInstructions::iBit},
		{0x30, ControlFlowInstructions::iBmi},
		{0x38, ControlFlowInstructions::iSec},

		{0x40, ControlFlowInstructions::iRti},
		{0x48, ControlFlowInstructions::iPha},
		{0x4C, ControlFlowInstructions::iJmp},
		{0x50, ControlFlowInstructions::iBvc},
		{0x58, ControlFlowInstructions::iCli},

		{0x60, ControlFlowInstructions::iRts},
		{0x68, ControlFlowInstructions::iPla},
		{0x6C, ControlFlowInstructions::iJmp},
		{0x70, ControlFlowInstructions::iBvs},
		{0x78, ControlFlowInstructions::iSei}
	};

	static std::map<uint8_t, ControlFlowInstructionAddressingMode> CFHexToDecodeMode
	{
		{0x00, ControlFlowInstructionAddressingMode::implied},
		{0x88, ControlFlowInstructionAddressingMode::implied},
		{0x10, ControlFlowInstructionAddressingMode::relative},
		{0x18, ControlFlowInstructionAddressingMode::implied},

		{0x20, ControlFlowInstructionAddressingMode::absolute},
		{0x24, ControlFlowInstructionAddressingMode::zeroPage},
		{0x28, ControlFlowInstructionAddressingMode::implied},
		{0x2C, ControlFlowInstructionAddressingMode::absolute},
		{0x30, ControlFlowInstructionAddressingMode::relative},
		{0x38, ControlFlowInstructionAddressingMode::implied},

		{0x40, ControlFlowInstructionAddressingMode::implied},
		{0x48, ControlFlowInstructionAddressingMode::implied},
		{0x4C, ControlFlowInstructionAddressingMode::absolute},
		{0x50, ControlFlowInstructionAddressingMode::relative},
		{0x58, ControlFlowInstructionAddressingMode::implied},

		{0x60, ControlFlowInstructionAddressingMode::implied},
		{0x68, ControlFlowInstructionAddressingMode::implied},
		{0x6C, ControlFlowInstructionAddressingMode::indirect},
		{0x70, ControlFlowInstructionAddressingMode::relative},
		{0x78, ControlFlowInstructionAddressingMode::implied}
	};

	static std::map<uint8_t, uint8_t> CFHexToCycleTime
	{
		{0x00, 7},
		{0x88, 3},
		{0x10, 2},
		{0x18, 2},

		{0x20, 6},
		{0x24, 3},
		{0x28, 4},
		{0x2C, 4},
		{0x30, 2},
		{0x38, 2},

		{0x40, 6},
		{0x48, 3},
		{0x4C, 3},
		{0x50, 2},
		{0x58, 2},

		{0x60, 6},
		{0x68, 4},
		{0x6C, 5},
		{0x70, 2},
		{0x78, 2}
	};

	static std::map<ControlFlowInstructionAddressingMode, uint8_t> ControlFlowInstructionSizes
	{
		{ControlFlowInstructionAddressingMode::relative, 2},
		{ControlFlowInstructionAddressingMode::zeroPage, 2},
		{ControlFlowInstructionAddressingMode::indirect, 3},
		{ControlFlowInstructionAddressingMode::absolute, 3},
		{ControlFlowInstructionAddressingMode::implied, 1}
	};
	
}