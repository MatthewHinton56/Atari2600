#pragma once
#include "../MOS6507Constants.h"

namespace mos6507
{
	inline uint8_t convertByteToBCD(Byte input)
	{
		uint8_t highOrder = (input & 0xF0) * 10;
		uint8_t lowOrder = (input & 0x0F);

		return highOrder + lowOrder;
	}

	inline Byte convertBCDTOByte(uint8_t input)
	{
		uint8_t highOrder = input / 10;
		uint8_t lowOrder = input % 10;

		return (highOrder << 4) | lowOrder;
	}

	inline Byte addWithCarryBSD
	(
		Byte operand1,
		Byte operand2,
		Byte statusRegister
	)
	{
		uint8_t dec1 = convertByteToBCD(operand1);
		uint8_t dec2 = convertByteToBCD(operand2);

		uint8_t sum = dec1 + dec2 + (getCarryFlag(statusRegister));
		clearCarryFlag(statusRegister);

		if (sum >= 100)
		{
			sum -= 100;
			setCarryFlag(statusRegister);
		}

		Byte bsd = convertBCDTOByte(sum);

		(!bsd) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(0x80 & bsd) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		setOverflowFlag(statusRegister);

		return bsd;
	}

	inline Byte subtracWithCarryBSD
	(
		Byte operand1,
		Byte operand2,
		Byte statusRegister
	)
	{
		int8_t dec1 = convertByteToBCD(operand1);
		int8_t dec2 = convertByteToBCD(operand2);

		int8_t result = dec1 - dec2 + (getCarryFlag(statusRegister)) - 1;
		setCarryFlag(statusRegister);

		if (result < 0)
		{
			result = 99 + result + 1;
			clearCarryFlag(statusRegister);
		}

		Byte bsd = convertBCDTOByte(result);

		(!bsd) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(0x80 & bsd) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		setOverflowFlag(statusRegister);

		return bsd;
	}

}