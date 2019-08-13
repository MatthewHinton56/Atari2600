#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeAccumulator : uint8_t
	{
		read,
		write,
		rmw
	};

	enum class InstructionOpcodeAccumulator : uint8_t
	{
		iAsl = 0x0A,
		iRol = 0x2A,
		iLsr = 0x4A,
		iRor = 0x6A
	};

	static std::unordered_map< InstructionOpcodeAccumulator, InstructionTypeAccumulator> InstructionToTypeAccumulator
	{
		{InstructionOpcodeAccumulator::iAsl, InstructionTypeAccumulator::read},
		{InstructionOpcodeAccumulator::iRol, InstructionTypeAccumulator::read},
		{InstructionOpcodeAccumulator::iLsr, InstructionTypeAccumulator::read},
		{InstructionOpcodeAccumulator::iRor, InstructionTypeAccumulator::read}
	};

	static std::unordered_map< InstructionOpcodeAccumulator, InstructionGroups> InstructionToGroupAccumulator
	{
		{InstructionOpcodeAccumulator::iAsl, InstructionGroups::asl},
		{InstructionOpcodeAccumulator::iRol, InstructionGroups::rol},
		{InstructionOpcodeAccumulator::iLsr, InstructionGroups::lsr},
		{InstructionOpcodeAccumulator::iRor, InstructionGroups::ror}
	};
}