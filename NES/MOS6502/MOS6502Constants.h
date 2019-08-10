#pragma once
#include "../Memory.h"
#include <cstdint>
#include <vector>
#include <array>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <map>

#define getCarryFlag(x) x & 0x1
#define getZeroFlag(x) ((x & 0x2) >> 1)
#define getInterruptFlag(x) ((x & 0x4) >> 2)
#define getDecimalFlag(x) ((x & 0x8) >> 3)
#define getBreakFlag(x) ((x & 0x10) >> 4)
#define getOverflowFlag(x) ((x & 0x40) >> 6)
#define getNegativeFlag(x) ((x & 0x80) >> 7)

#define setCarryFlag(x) x = (x | 0x1)
#define setZeroFlag(x) x = (x | 0x2)
#define setInterruptFlag(x) x = (x | 0x4)
#define setDecimalFlag(x) x = (x | 0x8)
#define setBreakFlag(x) x = (x | 0x10)
#define setOverflowFlag(x) x = (x | 0x40)
#define setNegativeFlag(x) x = (x | 0x80)

#define clearCarryFlag(x) x = (x & ~0x1)
#define clearZeroFlag(x) x = (x & ~0x2)
#define clearInterruptFlag(x) x = (x & ~0x4)
#define clearDecimalFlag(x) x = (x & ~0x8)
#define clearBreakFlag(x) x = (x & ~0x10)
#define clearOverflowFlag(x) x = (x & ~0x40)
#define clearNegativeFlag(x) x = (x & ~0x80)

#define generateAC(A, C) ((C & 0x3) | (A << 0x2)) 
#define generateCA(A, C) ((C << 0x3) | (A & 0x7)) 
#define generateABC(A, B, C) ((A << 0x5) | (B << 0x2) | C) 

namespace mos6502
{

	typedef std::array<Byte, 5> RegisterMap;

	static const unsigned int NUM_PAGES = 256;
	static const unsigned int PAGE_SIZE = 256;
	
	static const unsigned int aMask = 0xE0;
	static const unsigned int bMask = 0x1C;
	static const unsigned int cMask = 0x02;

	static const Word IRQ_VECTOR = 0xFFFE;

	static const Word NMI_VECTOR = 0xFFFA;

	static const Word RESET_VECTOR = 0xFFFC;

	static const int8_t AC = 0;
	static const int8_t  SR = 1;
	static const int8_t  Y = 2;
	static const int8_t  X = 3;
	static const int8_t  SP = 4;

}

