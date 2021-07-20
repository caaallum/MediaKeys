
#ifndef __MEDIAKEYS__
#define __MEDIAKEYS__
#include <stdio.h>
#ifdef WIN32
#include <Windows.h>

HHOOK g_hook;

LRESULT
CALLBACK
KeyboardProc(int, WPARAM, LPARAM);

BOOL
IsControlComboActive();
#else
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

int
main(int argc, char const *argv[]);

BOOL
IsControlComboActive();

void
SimulateKeyPress(KeySym);

BOOL
IsKeyActive(KeySym);

#endif //!WIN32

#endif //!__MEDIAKEYS__