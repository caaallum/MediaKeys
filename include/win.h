#ifndef MEDIAKEYS_WIN_H
#define MEDIAKEYS_WIN_H


#include <Windows.h>
HHOOK g_hook;

void Start();

LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);

BOOL IsControlComboActive();

#endif//MEDIAKEYS_WIN_H
