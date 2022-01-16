#ifndef MEDIAKEYS_LINUX_H
#define MEDIAKEYS_LINUX_H

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

void Start();

Bool IsControlComboActive();

void SimulateKeyPress(KeySym);

Bool IsKeyActive(KeySym);

#endif//MEDIAKEYS_LINUX_H
