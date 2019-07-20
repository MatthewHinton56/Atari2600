#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <cmath>
#include <stdexcept>
#include <iostream>

namespace mos6507
{
	template<size_t pageSize, size_t numPages>
	class Memory
	{
	public:

		
		Memory
		(

		) :
			pageAddressSize(log2(numPages)),
			offsetAddressSize(log2(pageSize)),
			addressSize(pageAddressSize + offsetAddressSize),
			memory()
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

		inline uint8_t& operator[](unsigned int i)
		{
			if ((~getAddressMask() & i))
			{
				throw std::invalid_argument("Invalid Address");
			}
			return memory[i];
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

		inline unsigned int getTotalBytes() const
		{
			return memory.size();
		}

		inline unsigned int getPageMask() const
		{
			unsigned int mask = ((1 << pageAddressSize) - 1) << offsetAddressSize;
			std::cout << mask << std::endl;
			return mask;
		}

		inline unsigned int getOffsetMask() const
		{
			unsigned int mask = ((1 << offsetAddressSize) - 1);
			std::cout << mask << std::endl;
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


	private:

		const unsigned int pageAddressSize;
		const unsigned int offsetAddressSize;
		const unsigned int addressSize;

		std::array<uint8_t, numPages * pageSize> memory;


	};

}