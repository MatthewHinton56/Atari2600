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
		iBcc,
		iTya,
		iTay,
		iBcs,
		iClv,
		inc,
		iBne,
		iCld,
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
		dec,
		nop
	};

}