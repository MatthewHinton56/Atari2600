#pragma once
#include "../MOS6507Constants.h"

namespace mos6507
{
	inline Byte addWithCarry
	(
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
	)
	{
		bool carry = getCarryFlag(statusRegister);

		int16_t temp = operand1 + operand2 + carry;
		clearCarryFlag(statusRegister);

		(temp < -128  || temp > 127) ? setOverflowFlag(statusRegister) : clearOverflowFlag(statusRegister);

		(temp > 255) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);

		Byte sum = temp & 0xFF;

		(!sum) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(0x80 & sum) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);
	};

	inline Byte subtractWithCarry
	(
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
	)
	{
		bool carry = getCarryFlag(statusRegister);

		int8_t result = operand1 + operand2 - 1 + carry;
		clearCarryFlag(statusRegister);

		(result < 0) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);

		(!result) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		bool sign1 = (0x80 & operand1);
		bool sign2 = (0x80 & operand2);
		bool signSum = (0x80 & result);

		(sign1 == sign2 && sign1 != signSum) ? setOverflowFlag(statusRegister) : clearOverflowFlag(statusRegister);

		(signSum) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		return result;
	};

	inline void compare
	(
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
	)
	{
		(operand1 > operand2) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);

		(operand1 == operand2) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(operand1 >= 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);
	};

	enum class LogicOperator
	{
		AND,
		OR,
		XOR
	};

	inline Byte logic
	(
		LogicOperator op,
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
	)
	{
		Byte result = 0;

		switch (op)
		{
		case LogicOperator::AND:
				result = operand1 & operand2;
				break;
		case LogicOperator::OR:
				result = operand1 | operand2;
				break;
		case LogicOperator::XOR:
				result = operand1 ^ operand2;
				break;
		}
		
		(result) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(result >= 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		return result;
	};

	enum class ShiftOperator
	{
		ASL,
		LSR,
		ROR,
		ROL
	};

	inline Byte logic
	(
		ShiftOperator op,
		Byte operand,
		Byte& statusRegister
	)
	{
		Byte result = 0;
		bool carry = getCarryFlag(statusRegister);
		bool temp;
		switch (op)
		{
		case ShiftOperator::ASL:
			(0x80 & operand) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);
			result = operand << 1;
			break;
		case ShiftOperator::LSR:
			(0x1 & operand) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);
			result = operand >> 1;
			break;
		case ShiftOperator::ROR:
			temp = (0x1 & operand);
			result = operand >> 1;
			result |= (getCarryFlag(statusRegister)) << 7;
			(temp) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);
			break;
		case ShiftOperator::ROL:
			temp = (0x80 & operand);
			result = operand << 1;
			result |= (getCarryFlag(statusRegister));
			(temp) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);
			break;
		}

		(result) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(result >= 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		return result;
	};
}