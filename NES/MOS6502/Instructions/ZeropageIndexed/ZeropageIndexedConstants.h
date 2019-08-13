#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeZeropageIndexed : uint8_t
	{
		read,
		write,
		rmw
	};

	enum class InstructionOpcodeZeropageIndexed : uint8_t
	{
		iNop1 = 0x14,
		iNop2 = 0x34,
		iNop3 = 0x54,
		iNop4 = 0x74,
		iSty = 0x94,
		iLdy = 0xB4,
		iNop5 = 0xD4,
		iNop6 = 0xF4,
		iOra = 0x15,
		iAnd = 0x35,
		iEor = 0x55,
		iAdc = 0x75,
		iSta = 0x95,
		iLda = 0xB5,
		iCmp = 0xD5,
		iSbc = 0xF5,
		iAsl = 0x16,
		iRol = 0x36,
		iLsr = 0x56,
		iRor = 0x76,
		iStx = 0x96,
		iLdx = 0xB6,
		iDec = 0xD6,
		iInc = 0xF6
	};

	static std::unordered_map< InstructionOpcodeZeropageIndexed, InstructionTypeZeropageIndexed> InstructionToTypeZeropageIndexed
	{
		{InstructionOpcodeZeropageIndexed::iNop1, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iNop2, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iNop3, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iNop4, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iSty, InstructionTypeZeropageIndexed::write},
		{InstructionOpcodeZeropageIndexed::iLdy, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iNop5, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iNop6, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iOra, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iAnd, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iEor, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iAdc, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iSta, InstructionTypeZeropageIndexed::write},
		{InstructionOpcodeZeropageIndexed::iLda, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iCmp, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iSbc, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iAsl, InstructionTypeZeropageIndexed::rmw},
		{InstructionOpcodeZeropageIndexed::iRol, InstructionTypeZeropageIndexed::rmw},
		{InstructionOpcodeZeropageIndexed::iLsr, InstructionTypeZeropageIndexed::rmw},
		{InstructionOpcodeZeropageIndexed::iRor, InstructionTypeZeropageIndexed::rmw},
		{InstructionOpcodeZeropageIndexed::iStx, InstructionTypeZeropageIndexed::write},
		{InstructionOpcodeZeropageIndexed::iLdx, InstructionTypeZeropageIndexed::read},
		{InstructionOpcodeZeropageIndexed::iDec, InstructionTypeZeropageIndexed::rmw},
		{InstructionOpcodeZeropageIndexed::iInc, InstructionTypeZeropageIndexed::rmw}
	};

	static std::unordered_map< InstructionOpcodeZeropageIndexed, InstructionGroups> InstructionToGroupZeropageIndexed
	{
		{InstructionOpcodeZeropageIndexed::iNop1, InstructionGroups::nop},
		{InstructionOpcodeZeropageIndexed::iNop2, InstructionGroups::nop},
		{InstructionOpcodeZeropageIndexed::iNop3, InstructionGroups::nop},
		{InstructionOpcodeZeropageIndexed::iNop4, InstructionGroups::nop},
		{InstructionOpcodeZeropageIndexed::iSty, InstructionGroups::st},
		{InstructionOpcodeZeropageIndexed::iLdy, InstructionGroups::ld},
		{InstructionOpcodeZeropageIndexed::iNop5, InstructionGroups::nop},
		{InstructionOpcodeZeropageIndexed::iNop6, InstructionGroups::nop},
		{InstructionOpcodeZeropageIndexed::iOra, InstructionGroups::ora},
		{InstructionOpcodeZeropageIndexed::iAnd, InstructionGroups::nnand},
		{InstructionOpcodeZeropageIndexed::iEor, InstructionGroups::eor},
		{InstructionOpcodeZeropageIndexed::iAdc, InstructionGroups::adc},
		{InstructionOpcodeZeropageIndexed::iSta, InstructionGroups::st},
		{InstructionOpcodeZeropageIndexed::iLda, InstructionGroups::ld},
		{InstructionOpcodeZeropageIndexed::iCmp, InstructionGroups::cmp},
		{InstructionOpcodeZeropageIndexed::iSbc, InstructionGroups::sbc},
		{InstructionOpcodeZeropageIndexed::iAsl, InstructionGroups::asl},
		{InstructionOpcodeZeropageIndexed::iRol, InstructionGroups::rol},
		{InstructionOpcodeZeropageIndexed::iLsr, InstructionGroups::lsr},
		{InstructionOpcodeZeropageIndexed::iRor, InstructionGroups::ror},
		{InstructionOpcodeZeropageIndexed::iStx, InstructionGroups::st},
		{InstructionOpcodeZeropageIndexed::iLdx, InstructionGroups::ld},
		{InstructionOpcodeZeropageIndexed::iDec, InstructionGroups::dec},
		{InstructionOpcodeZeropageIndexed::iInc, InstructionGroups::inc}
	};
}