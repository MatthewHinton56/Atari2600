#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeIndirectY : uint8_t
	{
		read,
		write,
		rmw,
		iread //incorrect read
	};

	enum class InstructionOpcodeIndirectY : uint8_t
	{
		iOra = 0x11,
		iAnd = 0x31,
		iEor = 0x51,
		iAdc = 0x71,
		iSta = 0x91,
		iLda = 0xB1,
		iCmp = 0xD1,
		iSbc = 0xF1
	};

	static std::unordered_map< InstructionOpcodeIndirectY, InstructionTypeIndirectY> InstructionToTypeIndirectY
	{
		{InstructionOpcodeIndirectY::iOra, InstructionTypeIndirectY::read},
		{InstructionOpcodeIndirectY::iAnd, InstructionTypeIndirectY::read},
		{InstructionOpcodeIndirectY::iEor, InstructionTypeIndirectY::read},
		{InstructionOpcodeIndirectY::iAdc, InstructionTypeIndirectY::read},
		{InstructionOpcodeIndirectY::iSta, InstructionTypeIndirectY::write},
		{InstructionOpcodeIndirectY::iLda, InstructionTypeIndirectY::read},
		{InstructionOpcodeIndirectY::iCmp, InstructionTypeIndirectY::read},
		{InstructionOpcodeIndirectY::iSbc, InstructionTypeIndirectY::read}
	};

	static std::unordered_map< InstructionOpcodeIndirectY, InstructionGroups> InstructionToGroupIndirectY
	{
		{InstructionOpcodeIndirectY::iOra, InstructionGroups::ora},
		{InstructionOpcodeIndirectY::iAnd, InstructionGroups::nnand},
		{InstructionOpcodeIndirectY::iEor, InstructionGroups::eor},
		{InstructionOpcodeIndirectY::iAdc, InstructionGroups::adc},
		{InstructionOpcodeIndirectY::iSta, InstructionGroups::st},
		{InstructionOpcodeIndirectY::iLda, InstructionGroups::ld},
		{InstructionOpcodeIndirectY::iCmp, InstructionGroups::cmp},
		{InstructionOpcodeIndirectY::iSbc, InstructionGroups::sbc}
	};
}