#pragma once

#include <cstdint>

namespace mos6502
{
	//And is key word, so n(nand) is used 
	
	enum class InstructionGroups : int8_t
	{
		brk,
		php,
		clc,
		iJsr,
		bit,
		plp,
		sec,
		rti,
		pha,
		jmp,
		cli,
		rts,
		pla,
		sei,
		st,
		trf,
		clv,
		inc,
		cld,
		sed,
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
		ld,
		dec,
		nop,
		brn
	};

}