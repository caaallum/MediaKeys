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
int
main(int argc, char const* argv[]);

BOOL
IsControlComboActive();

void
SimulateKeyPress(KeySym);

BOOL
IsKeyActive(KeySym);
#endif//WIN32
#endif//__MEDIAKEYS__