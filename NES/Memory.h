#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <cmath>
#include <map>
#include <stdexcept>
#include <iostream>

namespace mos6502
{

	typedef uint16_t Word;
	typedef uint8_t Byte;
	typedef void (*MemoryListenerFunction)(Word, Byte, bool);

	template<size_t pageSize, size_t numPages>
	class Memory
	{
	public:

		Memory
		(

		) :
			pageAddressSize(static_cast<int>(log2(numPages))),
			offsetAddressSize(static_cast<int>(log2(pageSize))),
			addressSize(pageAddressSize + offsetAddressSize),
			memory(),
			memoryListeners()
		{
			if (!((pageSize & (pageSize - 1)) == 0))
			{
				throw std::invalid_argument("bytesPerPage must be a power of Two");
			}

			if (!((numPages & (numPages - 1)) == 0))
			{
				throw std::invalid_argument("numPages must be a power of Two");
			}
		}

		virtual ~Memory() = default;

		inline Byte readByte(Word address)
		{
			if (memoryListeners.find(address) != memoryListeners.end())
			{
				memoryListeners[address](address, 0, false);
			}

			return memory[address];
		}

		inline void writeByte(Word address, Byte val)
		{
			if (address < 0x2000)
			{
				Word baseAddress = address % 0x0800;

				address = baseAddress;
				memory[baseAddress]			 = val;
				memory[baseAddress + 0x0800] = val;
				memory[baseAddress + 0x1000] = val;
				memory[baseAddress + 0x1800] = val;
			}

			if (address >= 0x2000 && address < 0x4000)
			{
				Word baseAddress = (address % 0x8) + 0x2000;
				for (Word add = baseAddress; add < 0x4000; add += 0x8)
				{
					memory[add] = val; 
				}

				address = baseAddress;
			}

			if (memoryListeners.find(address) != memoryListeners.end())
			{
				memoryListeners[address](address, val, true);
			}

			memory[address] = val;
		}

		inline void addMemoryListener(Word address, MemoryListenerFunction function)
		{
			memoryListeners[address] = function;
		}

		inline unsigned int getPageSize() const
		{
			return pageSize;
		}

		inline unsigned int getNumPages() const
		{
			return numPages;
		}

		inline unsigned int getPageAddressSize() const
		{
			return pageAddressSize;
		}

		inline unsigned int getOffsetAddressSize() const
		{
			return offsetAddressSize;
		}

		inline unsigned int getAddressSize() const
		{
			return addressSize;
		}

		inline Word getTotalBytes() const
		{
			return ((Word)getAddressMask());
		}

		inline unsigned int getPageMask() const
		{
			unsigned int mask = ((1 << pageAddressSize) - 1) << offsetAddressSize;
			return mask;
		}

		inline unsigned int getOffsetMask() const
		{
			unsigned int mask = ((1 << offsetAddressSize) - 1);
			return mask;
		}

		inline unsigned int getAddressMask() const
		{
			return getOffsetMask() | getPageMask();
		}

		//Returns a Page of Memory
		inline std::array<uint8_t, pageSize> readPage
		(
			unsigned int pageNumber
		)
		{
			if (pageNumber > numPages)
			{
				throw std::invalid_argument("Page Number must be a valid page");
			}

			std::array<uint8_t, pageSize> page;
			for (int i = 0; i < pageSize; i++)
			{
				page[i] = memory[i + pageNumber * pageSize];
			}
			return page;
		}

		//Returns a Page of Memory
		inline void writePage
		(
			unsigned int pageNumber,
			std::array<uint8_t, pageSize> page
		)
		{
			if (pageNumber > numPages)
			{
				throw std::invalid_argument("Page Number must be a valid page");
			}

			for (int i = 0; i < pageSize; i++)
			{
				memory[i + pageNumber * pageSize] = page[i];
			}
		}

		inline void clearMemory()
		{
			memory.fill(0);
		}

		inline uint8_t& operator[](unsigned int i)
		{
			if ((~getAddressMask() & i))
			{
				throw std::invalid_argument("Invalid Address");
			}
			return memory[i];
		}

	private:

		const unsigned int pageAddressSize;
		const unsigned int offsetAddressSize;
		const unsigned int addressSize;

		std::array<Byte, numPages * pageSize> memory;

		std::map<Word, MemoryListenerFunction> memoryListeners;
	};
}