#pragma once

#include <cstdint>

namespace mos6502
{
	//And is key word, so n(nand) is used 
	
	enum class InstructionGroups : int8_t
	{
		brk,
		clc,
		jsr,
		bit,
		sec,
		rti,
		ph,
		jmp,
		cli,
		rts,
		pl,
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
		brn,
		spec
	};

}