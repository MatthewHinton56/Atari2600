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

	enum class arithmeticLogicInstructions
	{
		iOra = 010,
		iAnd,
		iEor,
		iAdc,
		iSta,
		iLda,
		iCmp,
		iSbc,
		iAsl,
		iRol,
		iLsr,
		iRor
	};


}