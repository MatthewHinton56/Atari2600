#pragma once

#define LinearCounter 0x4008
#define TimerLow	  0x400A
#define LengthCounter 0x400B

#define getControlFlag(memory) ((memory[LinearCounter] >> 7) & 0x1)
#define getCounterReloadValue(memory) ((memory[LinearCounter]) & 0x7F)

#define getTimerLow(memory) (memory[TimerLow])

#define getLengthCounterLoad(memory) ((memory[LengthCounter] >> 3) & 0x1F)
#define getTimerHigh(memory) ((memory[LengthCounter]) & 0x7)
