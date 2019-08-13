#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeAbsoluteIndexed : uint8_t
	{
		read,
		write,
		rmw,
		iread //incorrect read
	};

	enum class InstructionOpcodeAbsoluteIndexed : uint8_t
	{
		iOraY = 0x19,
		iAndY = 0x39,
		iEorY = 0x59,
		iAdcY = 0x79,
		iStaY = 0x99,
		iLdaY = 0xB9,
		iCmpY = 0xD9,
		iSbcY = 0xF9,
		iNop1 = 0x1C,
		iNop2 = 0x3C,
		iNop3 = 0x5C,
		iNop4 = 0x7C,
		iNop5 = 0x9C,
		iLdy = 0xBC,
		iNop6 = 0xDC,
		iNop7 = 0xFC,
		iOraX = 0x1D,
		iAndX = 0x3D,
		iEorX = 0x5D,
		iAdcX = 0x7D,
		iStaX = 0x9D,
		iLdaX = 0xBD,
		iCmpX = 0xDD,
		iSbcX = 0xFD,
		iAsl = 0x1E,
		iRol = 0x3E,
		iLsr = 0x5E,
		iRor = 0x7E,
		iNop8 = 0x9E,
		iLdx = 0xBE,
		iDec = 0xDE,
		iInc = 0xFE
	};

	static std::unordered_map< InstructionOpcodeAbsoluteIndexed, InstructionTypeAbsoluteIndexed> InstructionToTypeAbsoluteIndexed
	{
		{InstructionOpcodeAbsoluteIndexed::iNop1, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iNop2, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iNop3, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iNop4, InstructionTypeAbsoluteIndexed::write},
		{InstructionOpcodeAbsoluteIndexed::iLdy, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iNop5, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iNop6, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iOraY, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iAndY, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iEorY, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iAdcY, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iStaY, InstructionTypeAbsoluteIndexed::write},
		{InstructionOpcodeAbsoluteIndexed::iLdaY, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iCmpY, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iSbcY, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iOraX, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iAndX, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iEorX, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iAdcX, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iStaX, InstructionTypeAbsoluteIndexed::write},
		{InstructionOpcodeAbsoluteIndexed::iLdaX, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iCmpX, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iSbcX, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iAsl, InstructionTypeAbsoluteIndexed::rmw},
		{InstructionOpcodeAbsoluteIndexed::iRol, InstructionTypeAbsoluteIndexed::rmw},
		{InstructionOpcodeAbsoluteIndexed::iLsr, InstructionTypeAbsoluteIndexed::rmw},
		{InstructionOpcodeAbsoluteIndexed::iRor, InstructionTypeAbsoluteIndexed::rmw},
		{InstructionOpcodeAbsoluteIndexed::iNop7, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iLdx, InstructionTypeAbsoluteIndexed::read},
		{InstructionOpcodeAbsoluteIndexed::iDec, InstructionTypeAbsoluteIndexed::rmw},
		{InstructionOpcodeAbsoluteIndexed::iInc, InstructionTypeAbsoluteIndexed::rmw}
	};

	static std::unordered_map< InstructionOpcodeAbsoluteIndexed, InstructionGroups> InstructionToGroupAbsoluteIndexed
	{
		{InstructionOpcodeAbsoluteIndexed::iNop1, InstructionGroups::nop},
		{InstructionOpcodeAbsoluteIndexed::iNop2, InstructionGroups::nop},
		{InstructionOpcodeAbsoluteIndexed::iNop3, InstructionGroups::nop},
		{InstructionOpcodeAbsoluteIndexed::iNop4, InstructionGroups::nop},
		{InstructionOpcodeAbsoluteIndexed::iLdy, InstructionGroups::ld},
		{InstructionOpcodeAbsoluteIndexed::iNop5, InstructionGroups::nop},
		{InstructionOpcodeAbsoluteIndexed::iNop6, InstructionGroups::nop},
		{InstructionOpcodeAbsoluteIndexed::iOraY, InstructionGroups::ora},
		{InstructionOpcodeAbsoluteIndexed::iAndY, InstructionGroups::nnand},
		{InstructionOpcodeAbsoluteIndexed::iEorY, InstructionGroups::eor},
		{InstructionOpcodeAbsoluteIndexed::iAdcY, InstructionGroups::adc},
		{InstructionOpcodeAbsoluteIndexed::iStaY, InstructionGroups::st},
		{InstructionOpcodeAbsoluteIndexed::iLdaY, InstructionGroups::ld},
		{InstructionOpcodeAbsoluteIndexed::iCmpY, InstructionGroups::cmp},
		{InstructionOpcodeAbsoluteIndexed::iSbcY, InstructionGroups::sbc},
		{InstructionOpcodeAbsoluteIndexed::iOraX, InstructionGroups::ora},
		{InstructionOpcodeAbsoluteIndexed::iAndX, InstructionGroups::nnand},
		{InstructionOpcodeAbsoluteIndexed::iEorX, InstructionGroups::eor},
		{InstructionOpcodeAbsoluteIndexed::iAdcX, InstructionGroups::adc},
		{InstructionOpcodeAbsoluteIndexed::iStaX, InstructionGroups::st},
		{InstructionOpcodeAbsoluteIndexed::iLdaX, InstructionGroups::ld},
		{InstructionOpcodeAbsoluteIndexed::iCmpX, InstructionGroups::cmp},
		{InstructionOpcodeAbsoluteIndexed::iSbcX, InstructionGroups::sbc},
		{InstructionOpcodeAbsoluteIndexed::iAsl, InstructionGroups::asl},
		{InstructionOpcodeAbsoluteIndexed::iRol, InstructionGroups::rol},
		{InstructionOpcodeAbsoluteIndexed::iLsr, InstructionGroups::lsr},
		{InstructionOpcodeAbsoluteIndexed::iRor, InstructionGroups::ror},
		{InstructionOpcodeAbsoluteIndexed::iNop7, InstructionGroups::nop},
		{InstructionOpcodeAbsoluteIndexed::iLdx, InstructionGroups::ld},
		{InstructionOpcodeAbsoluteIndexed::iDec, InstructionGroups::dec},
		{InstructionOpcodeAbsoluteIndexed::iInc, InstructionGroups::inc}
	};
}