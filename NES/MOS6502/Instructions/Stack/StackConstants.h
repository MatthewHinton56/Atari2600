#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{

	enum class InstructionTypeStack : uint8_t
	{
		read,
		write,
		rmw
	};

	enum class InstructionOpcodeStack : uint8_t
	{
		iBrk = 0x00,
		iJsr = 0x20,
		iRti = 0x40,
		iRts = 0x60,
		iPhp = 0x08,
		iPlp = 0x28,
		iPha = 0x48,
		iPla = 0x68
	};

	static std::unordered_map< InstructionOpcodeStack, InstructionTypeStack> InstructionToTypeStack
	{
		{InstructionOpcodeStack::iBrk, InstructionTypeStack::write},
		{InstructionOpcodeStack::iJsr, InstructionTypeStack::write},
		{InstructionOpcodeStack::iRti, InstructionTypeStack::read},
		{InstructionOpcodeStack::iRts, InstructionTypeStack::read},
		{InstructionOpcodeStack::iPhp, InstructionTypeStack::write},
		{InstructionOpcodeStack::iPlp, InstructionTypeStack::read},
		{InstructionOpcodeStack::iPha, InstructionTypeStack::write},
		{InstructionOpcodeStack::iPla, InstructionTypeStack::read}
	};

	static std::unordered_map< InstructionOpcodeStack, InstructionGroups> InstructionToGroupStack
	{
		{InstructionOpcodeStack::iBrk, InstructionGroups::brk},
		{InstructionOpcodeStack::iJsr, InstructionGroups::jsr},
		{InstructionOpcodeStack::iRti, InstructionGroups::rti},
		{InstructionOpcodeStack::iRts, InstructionGroups::rts},
		{InstructionOpcodeStack::iPhp, InstructionGroups::ph},
		{InstructionOpcodeStack::iPlp, InstructionGroups::pl},
		{InstructionOpcodeStack::iPha, InstructionGroups::ph},
		{InstructionOpcodeStack::iPla, InstructionGroups::pl}
	};
}