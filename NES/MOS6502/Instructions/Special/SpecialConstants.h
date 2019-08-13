#pragma once

#include <cstdint>
#include <unordered_map>

namespace mos6502
{
	enum class InstructionSpecial : uint8_t
	{
		irq,
		nmi,
		reset
	};
}