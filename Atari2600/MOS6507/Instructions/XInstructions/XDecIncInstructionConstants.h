#pragma once
#include "../Binary.h"
#include "../InstructionConstants.h"

namespace mos6507
{
	enum class XDecIncInstructions
	{
		iStx = 024,
		iLdx,
		iDec,
		iInc,
		iTxa,
		iTxs,
		iTax,
		iTsx,
		iDex,
		iNop
	};



}