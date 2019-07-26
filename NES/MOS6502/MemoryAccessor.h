#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include "mos6502Constants.h"
#include "Memory.h"

namespace mos6502
{
	class MemoryAccessor
	{
		public:
			MemoryAccessor();

			virtual ~MemoryAccessor() = default;

			virtual Word readWord
			(
				Word address
			);

			virtual Word readWordNoCarry
			(
				Word address
			);

			virtual Word writeWord
			(
				Word address,
				Word data
			);

			virtual Word indirect
			(
				Word address
			);

			virtual Word xIndexIndirect
			(
				Byte address,
				Byte registerX
			);

			virtual Word yIndexIndirect
			(
				Byte address,
				Byte registerY,
				bool& crossedPage
			);

			inline uint8_t& operator[](unsigned int i)
			{
				return memory[i];
			}


			virtual Memory<PAGE_SIZE, NUM_PAGES>& getMemory();

		private:
			Memory<PAGE_SIZE, NUM_PAGES> memory;

	};
}
