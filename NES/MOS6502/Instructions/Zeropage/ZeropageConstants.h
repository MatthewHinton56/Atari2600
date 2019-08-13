#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeZeropage : uint8_t
	{
		read,
		write,
		rmw
	};

	enum class InstructionOpcodeZeropage : uint8_t
	{
		iNop1 = 0x04,
		iBit = 0x24,
		iNop2 = 0x44,
		iNop3 = 0x64,
		iSty = 0x84,
		iLdy = 0xA4,
		iCpy = 0xC4,
		iCpx = 0xE4,
		iOra = 0x05,
		iAnd = 0x25,
		iEor = 0x45,
		iAdc = 0x65,
		iSta = 0x85,
		iLda = 0xA5,
		iCmp = 0xC5,
		iSbc = 0xE5,
		iAsl = 0x06,
		iRol = 0x26,
		iLsr = 0x46,
		iRor = 0x66,
		iStx = 0x86,
		iLdx = 0xA6,
		iDec = 0xC6,
		iInc = 0xE6
	};

	static std::unordered_map< InstructionOpcodeZeropage, InstructionTypeZeropage> InstructionToTypeZeropage
	{
		{InstructionOpcodeZeropage::iNop1, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iNop2, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iNop3, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iBit, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iSty, InstructionTypeZeropage::write},
		{InstructionOpcodeZeropage::iLdy, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iCpy, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iCpx, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iOra, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iAnd, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iEor, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iAdc, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iSta, InstructionTypeZeropage::write},
		{InstructionOpcodeZeropage::iLda, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iCmp, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iSbc, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iAsl, InstructionTypeZeropage::rmw},
		{InstructionOpcodeZeropage::iRol, InstructionTypeZeropage::rmw},
		{InstructionOpcodeZeropage::iLsr, InstructionTypeZeropage::rmw},
		{InstructionOpcodeZeropage::iRor, InstructionTypeZeropage::rmw},
		{InstructionOpcodeZeropage::iStx, InstructionTypeZeropage::write},
		{InstructionOpcodeZeropage::iLdx, InstructionTypeZeropage::read},
		{InstructionOpcodeZeropage::iDec, InstructionTypeZeropage::rmw},
		{InstructionOpcodeZeropage::iInc, InstructionTypeZeropage::rmw}
	};

	static std::unordered_map< InstructionOpcodeZeropage, InstructionGroups> InstructionToGroupZeropage
	{
		{InstructionOpcodeZeropage::iNop1, InstructionGroups::nop},
		{InstructionOpcodeZeropage::iNop2, InstructionGroups::nop},
		{InstructionOpcodeZeropage::iNop3, InstructionGroups::nop},
		{InstructionOpcodeZeropage::iBit, InstructionGroups::bit},
		{InstructionOpcodeZeropage::iSty, InstructionGroups::st},
		{InstructionOpcodeZeropage::iLdy, InstructionGroups::ld},
		{InstructionOpcodeZeropage::iCpy, InstructionGroups::cmp},
		{InstructionOpcodeZeropage::iCpx, InstructionGroups::cmp},
		{InstructionOpcodeZeropage::iOra, InstructionGroups::ora},
		{InstructionOpcodeZeropage::iAnd, InstructionGroups::nnand},
		{InstructionOpcodeZeropage::iEor, InstructionGroups::eor},
		{InstructionOpcodeZeropage::iAdc, InstructionGroups::adc},
		{InstructionOpcodeZeropage::iSta, InstructionGroups::st},
		{InstructionOpcodeZeropage::iLda, InstructionGroups::ld},
		{InstructionOpcodeZeropage::iCmp, InstructionGroups::cmp},
		{InstructionOpcodeZeropage::iSbc, InstructionGroups::sbc},
		{InstructionOpcodeZeropage::iAsl, InstructionGroups::asl},
		{InstructionOpcodeZeropage::iRol, InstructionGroups::rol},
		{InstructionOpcodeZeropage::iLsr, InstructionGroups::lsr},
		{InstructionOpcodeZeropage::iRor, InstructionGroups::ror},
		{InstructionOpcodeZeropage::iStx, InstructionGroups::st},
		{InstructionOpcodeZeropage::iLdx, InstructionGroups::ld},
		{InstructionOpcodeZeropage::iDec, InstructionGroups::dec},
		{InstructionOpcodeZeropage::iInc, InstructionGroups::inc}
	};
}