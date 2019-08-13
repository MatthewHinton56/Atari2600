#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{
	enum class InstructionOpcodeRelative : uint8_t
	{
		iBpl = 0x10,
		iBmi = 0x30,
		iBvc = 0x50,
		iBvs = 0x70,
		iBcc = 0x90,
		iBcs = 0xB0,
		iBne = 0xD0,
		iBeq = 0xF0
	};
}