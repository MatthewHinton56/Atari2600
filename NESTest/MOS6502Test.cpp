#pragma once

#include "pch.h"

#include <chrono>


#define COMMA ,

using namespace mos6502;

namespace {

	class MOS6502Test : public ::testing::Test {
	protected:

		MOS6502Test() :
			mem(),
			mos(mem)
		{}


		void SetUp() override
		{

		}

		Memory<PAGE_SIZE, NUM_PAGES> mem;
		MOS6502 mos;
	};

}
