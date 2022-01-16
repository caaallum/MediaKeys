#ifndef __MEDIAKEYS__
#define __MEDIAKEYS__

#include <stdafx.h>

#ifdef WIN32

LRESULT
CALLBACK
KeyboardProc(int, WPARAM, LPARAM);

BOOL
IsControlComboActive();

#else

Bool
IsControlComboActive();

void
SimulateKeyPress(KeySym);

Bool
IsKeyActive(KeySym);

#endif//WIN32
#endif//__MEDIAKEYS__