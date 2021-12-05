#ifndef __STDAFX_H__
#define __STDAFX_H__

#include <stdio.h>

#ifdef WIN32
#   ifndef UNICODE
#       define UNICODE
#   endif//UNICODE
#   include <Windows.h>
HHOOK g_hook;
#else
#   include <X11/Xlib.h>
#   include <X11/extensions/XTest.h>
#   include <X11/keysym.h>
#   ifndef BOOLEAN
#   define BOOLEAN
    typedef int BOOL;
#   define TRUE 1
#   define FALSE 0
#endif//BOOLEAN
#endif//WIN32

#endif//__STDAFX_H__
