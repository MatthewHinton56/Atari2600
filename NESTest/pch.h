//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"
#include "Memory.h"
#include "mos6502\MOS6502.h"
#include "mos6502\Instructions\Binary.h"
#include "mos6502\Instructions\Absolute\Absolute.h"
#include "mos6502\Instructions\Zeropage\Zeropage.h"
#include "mos6502\Instructions\ZeropageIndexed\ZeropageIndexed.h"
#include "mos6502\Instructions\AbsoluteIndexed\AbsoluteIndexed.h"
#include "mos6502\Instructions\IndirectY\IndirectY.h"
#include "mos6502\Instructions\IndirectX\IndirectX.h"
#include "mos6502\Instructions\Indirect\Indirect.h"
#include "mos6502\Instructions\Relative\Relative.h"
#include "mos6502\Instructions\Immediate\Immediate.h"
#include "mos6502\Instructions\Accumulator\Accumulator.h"