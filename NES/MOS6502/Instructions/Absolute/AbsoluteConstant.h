#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeAbsolute : uint8_t
	{
		read,
		write,
		rmw,
		jmp
	};

	enum class InstructionOpcodeAbsolute : uint8_t
	{
		iNop = 0x0C,
		iBit = 0x2C,
		iJmp = 0x4C,
		iSty = 0x8C,
		iLdy = 0xAC,
		iCpy = 0xCC,
		iCpx = 0xEC,
		iOra = 0x0D,
		iAnd = 0x2D,
		iEor = 0x4D,
		iAdc = 0x6D,
		iSta = 0x8D,
		iLda = 0xAD,
		iCmp = 0xCD,
		iSbc = 0xED,
		iAsl = 0x0E,
		iRol = 0x2E,
		iLsr = 0x4E,
		iRor = 0x6E,
		iStx = 0x8E,
		iLdx = 0xAE,
		iDec = 0xCE,
		iInc = 0xEE
	};

	static std::unordered_map< InstructionOpcodeAbsolute, InstructionTypeAbsolute> InstructionToTypeAbsolute
	{
		{InstructionOpcodeAbsolute::iNop, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iBit, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iJmp, InstructionTypeAbsolute::jmp},
		{InstructionOpcodeAbsolute::iSty, InstructionTypeAbsolute::write},
		{InstructionOpcodeAbsolute::iLdy, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iCpy, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iCpx, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iOra, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iAnd, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iEor, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iAdc, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iSta, InstructionTypeAbsolute::write},
		{InstructionOpcodeAbsolute::iLda, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iCmp, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iSbc, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iAsl, InstructionTypeAbsolute::rmw},
		{InstructionOpcodeAbsolute::iRol, InstructionTypeAbsolute::rmw},
		{InstructionOpcodeAbsolute::iLsr, InstructionTypeAbsolute::rmw},
		{InstructionOpcodeAbsolute::iRor, InstructionTypeAbsolute::rmw},
		{InstructionOpcodeAbsolute::iStx, InstructionTypeAbsolute::write},
		{InstructionOpcodeAbsolute::iLdx, InstructionTypeAbsolute::read},
		{InstructionOpcodeAbsolute::iDec, InstructionTypeAbsolute::rmw},
		{InstructionOpcodeAbsolute::iInc, InstructionTypeAbsolute::rmw}
	};

	static std::unordered_map< InstructionOpcodeAbsolute, InstructionGroups> InstructionToGroupAbsolute
	{
		{InstructionOpcodeAbsolute::iNop, InstructionGroups::iNop},
		{InstructionOpcodeAbsolute::iBit, InstructionGroups::bit},
		{InstructionOpcodeAbsolute::iJmp, InstructionGroups::jmp},
		{InstructionOpcodeAbsolute::iSty, InstructionGroups::st},
		{InstructionOpcodeAbsolute::iLdy, InstructionGroups::ld},
		{InstructionOpcodeAbsolute::iCpy, InstructionGroups::cmp},
		{InstructionOpcodeAbsolute::iCpx, InstructionGroups::cmp},
		{InstructionOpcodeAbsolute::iOra, InstructionGroups::ora},
		{InstructionOpcodeAbsolute::iAnd, InstructionGroups::nnand},
		{InstructionOpcodeAbsolute::iEor, InstructionGroups::eor},
		{InstructionOpcodeAbsolute::iAdc, InstructionGroups::adc},
		{InstructionOpcodeAbsolute::iSta, InstructionGroups::st},
		{InstructionOpcodeAbsolute::iLda, InstructionGroups::ld},
		{InstructionOpcodeAbsolute::iCmp, InstructionGroups::cmp},
		{InstructionOpcodeAbsolute::iSbc, InstructionGroups::sbc},
		{InstructionOpcodeAbsolute::iAsl, InstructionGroups::asl},
		{InstructionOpcodeAbsolute::iRol, InstructionGroups::rol},
		{InstructionOpcodeAbsolute::iLsr, InstructionGroups::lsr},
		{InstructionOpcodeAbsolute::iRor, InstructionGroups::ror},
		{InstructionOpcodeAbsolute::iStx, InstructionGroups::st},
		{InstructionOpcodeAbsolute::iLdx, InstructionGroups::ld},
		{InstructionOpcodeAbsolute::iDec, InstructionGroups::dec},
		{InstructionOpcodeAbsolute::iInc, InstructionGroups::inc}
	};
}