#pragma once

#include <cstdint>

namespace mos6502
{
	//And is key word, so n(nand) is used 
	
	enum class InstructionGroups : int8_t
	{
		ibrk,
		iPhp,
		iClc,
		iJsr,
		bit,
		iPlp,
		iSec,
		iRti,
		iPha,
		jmp,
		iCli,
		iRts,
		iPla,
		iSei,
		st,
		iTya,
		iTay,
		iClv,
		inc,
		iCld,
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
		dec,
		nop,
		brn
	};

}