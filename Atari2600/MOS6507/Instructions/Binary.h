#pragma once
#include "../MOS6507Constants.h"

namespace mos6507
{
	inline Byte addWithCarry
	(
		Byte operand1,
		Byte operand2,
		Byte statusRegister
	)
	{
		bool carry = getCarryFlag(statusRegister);

		Byte sum = operand1 + operand2 + carry;
	};
}