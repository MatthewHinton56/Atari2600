#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeindirectX : uint8_t
	{
		read,
		write,
		rmw
	};

	enum class InstructionOpcodeindirectX : uint8_t
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

	static std::unordered_map< InstructionOpcodeindirectX, InstructionTypeindirectX> InstructionToTypeindirectX
	{
		{InstructionOpcodeindirectX::iOra, InstructionTypeindirectX::read},
		{InstructionOpcodeindirectX::iAnd, InstructionTypeindirectX::read},
		{InstructionOpcodeindirectX::iEor, InstructionTypeindirectX::read},
		{InstructionOpcodeindirectX::iAdc, InstructionTypeindirectX::read},
		{InstructionOpcodeindirectX::iSta, InstructionTypeindirectX::write},
		{InstructionOpcodeindirectX::iLda, InstructionTypeindirectX::read},
		{InstructionOpcodeindirectX::iCmp, InstructionTypeindirectX::read},
		{InstructionOpcodeindirectX::iSbc, InstructionTypeindirectX::read}
	};

	static std::unordered_map< InstructionOpcodeindirectX, InstructionGroups> InstructionToGroupindirectX
	{
		{InstructionOpcodeindirectX::iOra, InstructionGroups::ora},
		{InstructionOpcodeindirectX::iAnd, InstructionGroups::nnand},
		{InstructionOpcodeindirectX::iEor, InstructionGroups::eor},
		{InstructionOpcodeindirectX::iAdc, InstructionGroups::adc},
		{InstructionOpcodeindirectX::iSta, InstructionGroups::st},
		{InstructionOpcodeindirectX::iLda, InstructionGroups::ld},
		{InstructionOpcodeindirectX::iCmp, InstructionGroups::cmp},
		{InstructionOpcodeindirectX::iSbc, InstructionGroups::sbc}
	};
}