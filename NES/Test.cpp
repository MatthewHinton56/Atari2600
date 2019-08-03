#include "Memory.h"
#include <iostream>
#include "MOS6502/MOS6502Constants.h"
#include "MOS6502/MOS6502.h"
#include <time.h>
#include <windows.h>
#include <chrono>
#include "MOS6502/Instructions/XDecIncInstructions/XDecIncInstruction.h"
using namespace std;
using namespace mos6502;

BOOLEAN nanosleep(LONGLONG ns) {
	/* Declarations */
	HANDLE timer;	/* Timer handle */
	LARGE_INTEGER li;	/* Time defintion */
	/* Create timer */
	if (!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
		return FALSE;
	/* Set timer properties */
	li.QuadPart = -ns;
	if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
		CloseHandle(timer);
		return FALSE;
	}
	/* Start & wait for timer */
	WaitForSingleObject(timer, INFINITE);
	/* Clean resources */
	CloseHandle(timer);
	/* Slept without problems */
	return TRUE;
}


int main()
{
	Memory<PAGE_SIZE, NUM_PAGES> mem;
	MemoryAccessor memory(mem);
	RegisterMap registerMap;
	MOS6502 mos(mem);

	for (int i = 0; i < PAGE_SIZE * NUM_PAGES; i++)
	{
		mem[i] = 0xE8;
	}

	auto start = std::chrono::high_resolution_clock::now();

	XDecIncInstruction in(6, 2, 2, 0);

	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";

	 start = std::chrono::high_resolution_clock::now();

	in.decode(registerMap, memory);

	 finish = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";

	start = std::chrono::high_resolution_clock::now();

	in.execute(registerMap);

	finish = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";

	start = std::chrono::high_resolution_clock::now();

	in.writeBack(registerMap, memory);

	finish = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";

	start = std::chrono::high_resolution_clock::now();

	in.pc();

	finish = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
}