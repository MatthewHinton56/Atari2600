#include "Memory.h"
#include <iostream>
#include "MOS6502/MOS6502Constants.h"
#include "MOS6502/MOS6502.h"
#include <time.h>
#include <windows.h>
#include <chrono>
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
}