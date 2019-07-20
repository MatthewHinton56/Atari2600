#pragma once
#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <map>

namespace mos6507
{
	typedef uint16_t Word;
	typedef uint8_t Byte;

	typedef std::map<std::string, Byte> RegisterMap;

	static const unsigned int NUM_PAGES = 32;
	static const unsigned int PAGE_SIZE = 256;

	enum class instructionAddressingMode
	{
		xIndirect,
		zeroPage,
		immediate,
		absolute,
		yIndirect,
		xZeroPage,
		absoluteY,
		absoulateX
	};
}