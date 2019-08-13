#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeImmediate : uint8_t
	{
		read,
		write,
		rmw
	};

	enum class InstructionOpcodeImmediate : uint8_t
	{
		iLdy = 0xA0,
		iCpy = 0xC0,
		iCpx = 0xE0,
		iOra = 0x09,
		iAnd = 0x29,
		iEor = 0x49,
		iAdc = 0x69,
		iLda = 0xA9,
		iCmp = 0xC9,
		iSbc = 0xE9,
		iLdx = 0xA2
	};

	static std::unordered_map< InstructionOpcodeImmediate, InstructionTypeImmediate> InstructionToTypeImmediate
	{
		{InstructionOpcodeImmediate::iLdy, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iCpy, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iCpx, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iOra, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iAnd, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iEor, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iAdc, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iLda, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iCmp, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iSbc, InstructionTypeImmediate::read},
		{InstructionOpcodeImmediate::iLdx, InstructionTypeImmediate::read}
	};

	static std::unordered_map< InstructionOpcodeImmediate, InstructionGroups> InstructionToGroupImmediate
	{
		{InstructionOpcodeImmediate::iLdy, InstructionGroups::ld},
		{InstructionOpcodeImmediate::iCpy, InstructionGroups::cmp},
		{InstructionOpcodeImmediate::iCpx, InstructionGroups::cmp},
		{InstructionOpcodeImmediate::iOra, InstructionGroups::ora},
		{InstructionOpcodeImmediate::iAnd, InstructionGroups::nnand},
		{InstructionOpcodeImmediate::iEor, InstructionGroups::eor},
		{InstructionOpcodeImmediate::iAdc, InstructionGroups::adc},
		{InstructionOpcodeImmediate::iLda, InstructionGroups::ld},
		{InstructionOpcodeImmediate::iCmp, InstructionGroups::cmp},
		{InstructionOpcodeImmediate::iSbc, InstructionGroups::sbc},
		{InstructionOpcodeImmediate::iLdx, InstructionGroups::ld}
	};
}