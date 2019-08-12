#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeIndirectX : uint8_t
	{
		read,
		write,
		rmw
	};

	enum class InstructionOpcodeIndirectX : uint8_t
	{
		iOra = 0x01,
		iAnd = 0x21,
		iEor = 0x41,
		iAdc = 0x61,
		iSta = 0x81,
		iLda = 0xA1,
		iCmp = 0xC1,
		iSbc = 0xE1
	};

	static std::unordered_map< InstructionOpcodeIndirectX, InstructionTypeIndirectX> InstructionToTypeIndirectX
	{
		{InstructionOpcodeIndirectX::iOra, InstructionTypeIndirectX::read},
		{InstructionOpcodeIndirectX::iAnd, InstructionTypeIndirectX::read},
		{InstructionOpcodeIndirectX::iEor, InstructionTypeIndirectX::read},
		{InstructionOpcodeIndirectX::iAdc, InstructionTypeIndirectX::read},
		{InstructionOpcodeIndirectX::iSta, InstructionTypeIndirectX::write},
		{InstructionOpcodeIndirectX::iLda, InstructionTypeIndirectX::read},
		{InstructionOpcodeIndirectX::iCmp, InstructionTypeIndirectX::read},
		{InstructionOpcodeIndirectX::iSbc, InstructionTypeIndirectX::read}
	};

	static std::unordered_map< InstructionOpcodeIndirectX, InstructionGroups> InstructionToGroupIndirectX
	{
		{InstructionOpcodeIndirectX::iOra, InstructionGroups::ora},
		{InstructionOpcodeIndirectX::iAnd, InstructionGroups::nnand},
		{InstructionOpcodeIndirectX::iEor, InstructionGroups::eor},
		{InstructionOpcodeIndirectX::iAdc, InstructionGroups::adc},
		{InstructionOpcodeIndirectX::iSta, InstructionGroups::st},
		{InstructionOpcodeIndirectX::iLda, InstructionGroups::ld},
		{InstructionOpcodeIndirectX::iCmp, InstructionGroups::cmp},
		{InstructionOpcodeIndirectX::iSbc, InstructionGroups::sbc}
	};
}