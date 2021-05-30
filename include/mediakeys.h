
#ifndef __MEDIAKEYS__
#define __MEDIAKEYS__

#include <Windows.h>
#include <stdio.h>

HHOOK g_hook;

BOOL
IsShiftActive();

BOOL
IsControlActive();

BOOL
IsAltActive();

BOOL
IsRightArrowActive();

BOOL
IsLeftArrowActive();

LRESULT
CALLBACK
KeyboardProc(int, WPARAM, LPARAM);

#endif //!__MEDIAKEYS__