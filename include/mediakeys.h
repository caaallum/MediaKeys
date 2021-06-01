
#ifndef __MEDIAKEYS__
#define __MEDIAKEYS__

#include <Windows.h>
#include <stdio.h>

HHOOK g_hook;

LRESULT
CALLBACK
KeyboardProc(int, WPARAM, LPARAM);

BOOL
IsControlComboActive();

#endif //!__MEDIAKEYS__