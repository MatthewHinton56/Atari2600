#pragma once

namespace mos6502
{
	//And is key word, so n(nand) is used 
	
	enum class InstructionGroups
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
		iJmp,
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