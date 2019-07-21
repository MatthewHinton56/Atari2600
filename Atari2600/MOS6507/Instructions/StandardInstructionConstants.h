#pragma once
#pragma once
#include "Binary.h"
#include <cstdint>
#include <vector>
#include <array>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <map>

namespace mos6507
{

	static const uint8_t A = 2;

	enum class StandardInstructions
	{
		iOra = 010,
		iAnd,
		iEor,
		iAdc,
		iSta,
		iLda,
		iCmp,
		iSbc,
		iAsl = 020,
		iRol,
		iLsr,
		iRor
	};

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

	static std::map<InstructionAddressingMode, uint8_t> specialCycleTimes
	{
		{InstructionAddressingMode::zeroPage, 5},
		{InstructionAddressingMode::immediate, 2}, //A
		{InstructionAddressingMode::xZeroPage, 6},
		{InstructionAddressingMode::absolute, 6},
		{InstructionAddressingMode::absoluteX, 7}

	};

	static std::map<InstructionAddressingMode, uint8_t> cycleTimes
	{
		{InstructionAddressingMode::xIndirect, 4},
		{InstructionAddressingMode::zeroPage, 1},
		{InstructionAddressingMode::immediate, 0},
		{InstructionAddressingMode::absolute, 2},
		{InstructionAddressingMode::yIndirect, 3},
		{InstructionAddressingMode::xZeroPage, 2},
		{InstructionAddressingMode::absoluteY, 2},
		{InstructionAddressingMode::absoluteX, 2}
	};

	static std::map<InstructionAddressingMode, uint8_t> InstructionSizes
	{
		{InstructionAddressingMode::xIndirect, 2},
		{InstructionAddressingMode::zeroPage, 2},
		{InstructionAddressingMode::immediate, 2},
		{InstructionAddressingMode::absolute, 2},
		{InstructionAddressingMode::yIndirect, 2},
		{InstructionAddressingMode::xZeroPage, 2},
		{InstructionAddressingMode::absoluteY, 3},
		{InstructionAddressingMode::absoluteX, 3}
	};

	static std::map<StandardInstructions, LogicOperator> logicFunctions
	{
		{StandardInstructions::iOra, LogicOperator::OR},
		{StandardInstructions::iEor, LogicOperator::XOR},
		{StandardInstructions::iAnd, LogicOperator::AND}
	};

	static std::map<StandardInstructions, ArithmeticOperator> arithmeticFunctions
	{
		{StandardInstructions::iCmp, ArithmeticOperator::CMP},
		{StandardInstructions::iAdc, ArithmeticOperator::ADD},
		{StandardInstructions::iSbc, ArithmeticOperator::SUB}
	};

	static std::map<StandardInstructions, ShiftOperator> shiftFunctions
	{
		{StandardInstructions::iRor, ShiftOperator::ROR},
		{StandardInstructions::iRol, ShiftOperator::ROL},
		{StandardInstructions::iAsl, ShiftOperator::ASL},
		{StandardInstructions::iLsr, ShiftOperator::LSR}
	};

}