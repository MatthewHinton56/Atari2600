#pragma once

namespace mos6507
{
	enum class InstructionAddressingMode
	{
		xIndirect,
		zeroPage,
		immediate,
		absolute,
		yIndirect,
		xZeroPage,
		absoluteY,
		absoluteX
	};
}