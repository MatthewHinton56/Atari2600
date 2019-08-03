#pragma once

namespace mos6502
{
	enum class SpecialInstructionAddressingMode : uint8_t
	{
		implied
	};

	enum class SpecialInstructions : uint8_t
	{
		iBrkNmi,
		iBrkIrq
	};

	static std::map<SpecialInstructions, SpecialInstructionAddressingMode> instructionToDecodeMode
	{
		{SpecialInstructions::iBrkIrq, SpecialInstructionAddressingMode::implied},
		{SpecialInstructions::iBrkNmi, SpecialInstructionAddressingMode::implied}
	};

	static std::map<SpecialInstructions, uint8_t> ScycleTimes
	{
		{SpecialInstructions::iBrkIrq, 7},
		{SpecialInstructions::iBrkNmi, 7}
	};

	static std::map<SpecialInstructions, uint8_t> SInstructionSizes
	{
		{SpecialInstructions::iBrkIrq, 0},
		{SpecialInstructions::iBrkNmi, 0}
	};

}