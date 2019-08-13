#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeImplied : uint8_t
	{
		read,
		write,
		rmw
	};

	enum class InstructionOpcodeImplied : uint8_t
	{
		iDey = 0x88,
		iTay = 0xA8,
		iIny = 0xC8,
		iInx = 0xE8,

		iTxa = 0x8A,
		iTax = 0xAA,
		iDex = 0xCA,
		iNop = 0xEA,

		iClc = 0x18,
		iSec = 0x38,
		iCli = 0x58,
		iSei = 0x78,
		iTya = 0x98,
		iClv = 0xB8,
		iCld = 0xD8,
		iSed = 0xF8,

		iTxs = 0x9A,
		iTsx = 0xBA
	};

	static std::unordered_map< InstructionOpcodeImplied, InstructionGroups> InstructionToGroupImplied
	{
		{InstructionOpcodeImplied::iDey, InstructionGroups::dec},
		{InstructionOpcodeImplied::iTay, InstructionGroups::trf},
		{InstructionOpcodeImplied::iIny, InstructionGroups::inc},
		{InstructionOpcodeImplied::iInx, InstructionGroups::inc},
		{InstructionOpcodeImplied::iTxa, InstructionGroups::trf},
		{InstructionOpcodeImplied::iDex, InstructionGroups::dec},
		{InstructionOpcodeImplied::iNop, InstructionGroups::nop},
		{InstructionOpcodeImplied::iClc, InstructionGroups::clc},
		{InstructionOpcodeImplied::iSec, InstructionGroups::sec},
		{InstructionOpcodeImplied::iCli, InstructionGroups::cli},
		{InstructionOpcodeImplied::iSei, InstructionGroups::sei},
		{InstructionOpcodeImplied::iTya, InstructionGroups::trf},
		{InstructionOpcodeImplied::iClv, InstructionGroups::clv},
		{InstructionOpcodeImplied::iCld, InstructionGroups::cld},
		{InstructionOpcodeImplied::iSed, InstructionGroups::sed},
		{InstructionOpcodeImplied::iTxs, InstructionGroups::trf},
		{InstructionOpcodeImplied::iTsx, InstructionGroups::trf}
	};
}