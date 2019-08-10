#pragma once

#include <cstdint>

namespace mos6502
{
	//And is key word, so n(nand) is used 
	
	enum class InstructionGroups : int8_t
	{
		ibrk,
		iPhp,
		iBpl,
		iClc,
		iJsr,
		bit,
		iPlp,
		iBmi,
		iSec,
		iRti,
		iPha,
		jmp,
		iBvc,
		iCli,
		iRts,
		iPla,
		iBvs,
		iSei,
		st,
		iDey,
		iBcc,
		iTya,
		iTay,
		iBcs,
		iClv,
		iIny,
		iBne,
		iCld,
		iInx,
		iBeq,
		iSed,
		ora,
		nnand, 
		eor,
		adc,
		cmp,
		sbc,
		asl,
		rol,
		lsr,
		ror,
		iTxa,
		iTxs,
		ld,
		iTax,
		iTsx,
		iDec,
		iDex,
		iInc,
		iNop
	};

}