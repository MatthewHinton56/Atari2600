#pragma once
#include "../mos6502Constants.h"
namespace mos6502
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

		return sum;
	};

	inline Byte subtractWithCarry
	(
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
	)
	{
		bool carry = getCarryFlag(statusRegister);

		int16_t temp = (int8_t)operand1 - (int8_t)operand2 - 1 + carry;
		(temp < -128 || temp > 127) ? setOverflowFlag(statusRegister) : clearOverflowFlag(statusRegister);

		int8_t result = temp & 0xFF;
		clearCarryFlag(statusRegister);

		(result < 0) ? clearCarryFlag(statusRegister) : setCarryFlag(statusRegister);

		(!result) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		bool sign1 = (0x80 & operand1);
		bool sign2 = (0x80 & operand2);
		bool signSum = (0x80 & result);
		(signSum) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		return result;
	};

	inline Byte compare
	(
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
	)
	{
		(operand1 >= operand2) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);

		(operand1 == operand2) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(operand1 >= 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		return operand1;
	};

	inline Byte logic
	(
		InstructionGroups op,
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
	)
	{
		Byte result = 0;

		switch (op)
		{
			case InstructionGroups::nnand:
					result = operand1 & operand2;
					break;

			case InstructionGroups::ora:
					result = operand1 | operand2;
					break;

			case InstructionGroups::eor:
					result = operand1 ^ operand2;
					break;
		}
		
		(!result) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(result >= 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		return result;
	};

	inline Byte shift
	(
		InstructionGroups op,
		Byte operand,
		Byte& statusRegister
	)
	{
		Byte result = 0;
		bool carry = getCarryFlag(statusRegister);
		bool temp;
		switch (op)
		{
			case InstructionGroups::asl:
				(0x80 & operand) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);
				result = operand << 1;
				break;

			case InstructionGroups::lsr:
				(0x1 & operand) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);
				result = operand >> 1;
				break;

			case InstructionGroups::ror:
				temp = (0x1 & operand);
				result = operand >> 1;
				result |= (getCarryFlag(statusRegister)) << 7;
				(temp) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);
				break;

			case InstructionGroups::rol:
				temp = (0x80 & operand);
				result = operand << 1;
				result |= (getCarryFlag(statusRegister));
				(temp) ? setCarryFlag(statusRegister) : clearCarryFlag(statusRegister);
				break;
		}

		(!result) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(result >= 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		return result;
	};

	inline uint8_t convertByteToBCD(Byte input)
	{
		uint8_t highOrder = ((input & 0xF0) >> 4) * 10;
		uint8_t lowOrder = (input & 0x0F);

		return highOrder + lowOrder;
	}

	inline Byte convertBCDTOByte(uint8_t input)
	{
		uint8_t highOrder = input / 10;
		uint8_t lowOrder = input % 10;

		return (highOrder << 4) | lowOrder;
	}

	inline Byte addWithCarryBCD
	(
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
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

		Byte bcd = convertBCDTOByte(sum);

		(!bcd) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(0x80 & bcd) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		setOverflowFlag(statusRegister);

		return bcd;
	}

	inline Byte subtractWithCarryBCD
	(
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
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

		Byte bcd = convertBCDTOByte(result);

		(!bcd) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);

		(0x80 & bcd) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);

		setOverflowFlag(statusRegister);

		return bcd;
	}

	inline Byte arithmetic
	(
		InstructionGroups op,
		Byte operand1,
		Byte operand2,
		Byte& statusRegister
	)
	{
		bool isDec = getDecimalFlag(statusRegister);
		switch (op)
		{
		case InstructionGroups::adc:
			return (isDec) ?
				addWithCarryBCD(operand1, operand2, statusRegister) :
				addWithCarry(operand1, operand2, statusRegister);

		case InstructionGroups::sbc:
			return (isDec) ?
				subtractWithCarryBCD(operand1, operand2, statusRegister) :
				subtractWithCarry(operand1, operand2, statusRegister);

		case InstructionGroups::cmp:
			return compare(operand1, operand2, statusRegister);

		default:
			return Byte();
		}

	}

	inline Byte inc
	(
		Byte operand1,
		Byte& statusRegister
	)
	{
		Byte result = operand1 + 1;
		(result == 0) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);
		(result & 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);
		return result;
	}

	inline Byte dec
	(
		Byte operand1,
		Byte& statusRegister
	)
	{
		Byte result = operand1 - 1;
		(result == 0) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);
		(result & 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);
		return result;
	}

	inline void examine
	(
		Byte operand1,
		Byte& statusRegister
	)
	{
		(operand1 == 0) ? setZeroFlag(statusRegister) : clearZeroFlag(statusRegister);
		(operand1 & 0x80) ? setNegativeFlag(statusRegister) : clearNegativeFlag(statusRegister);
	}

}