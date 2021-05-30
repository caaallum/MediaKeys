#include "mediakeys.h"

int
WINAPI
wWinMain(
    _In_        HINSTANCE hInstance,
    _In_opt_    HINSTANCE hPrevInstance,
    _In_        PWSTR pCmdLine,
    _In_        int nCmdShow
)
{
    g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (g_hook == NULL)
    {
        MessageBox(NULL, L"Failed to set windows hook", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }
    while (GetMessage(NULL, NULL, 0, 0));

    UnhookWindowsHookEx(g_hook);

    return 0;
}

LRESULT 
CALLBACK
KeyboardProc(
    int nCode, 
    WPARAM wParam, 
    LPARAM lParam)
{
    INPUT input = { 0 };
    WCHAR buffer[50];
    if (wParam == WM_KEYDOWN)
    {

        KBDLLHOOKSTRUCT* hs = lParam;

        /* Next song */
        if (IsControlActive() && IsAltActive() && hs->vkCode == VK_RIGHT)
        {
            input.type      = INPUT_KEYBOARD;
            input.ki.wVk    = VK_MEDIA_NEXT_TRACK;
        }

        /* Previous song */
        if (IsControlActive() && IsAltActive() && hs->vkCode == VK_LEFT)
        {
            input.type      = INPUT_KEYBOARD;
            input.ki.wVk    = VK_MEDIA_PREV_TRACK;
        }

        if (IsControlActive() && IsAltActive() && hs->vkCode == VK_SPACE)
        {
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = VK_MEDIA_PLAY_PAUSE;
        }

        if (IsControlActive() && IsAltActive() && hs->vkCode == VK_OEM_PLUS)
        {
            input.type      = INPUT_KEYBOARD;
            input.ki.wVk    = VK_VOLUME_UP;
        }

        if (IsControlActive() && IsAltActive() && hs->vkCode == VK_OEM_MINUS)
        {
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = VK_VOLUME_DOWN;
        }

        UINT uSend = SendInput(1, &input, sizeof(INPUT));

        if (uSend != 1)
        {
            OutputDebugString(L"Failed to send input");
        }
    }

    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

BOOL
IsShiftActive()
{
    return GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0;
}

BOOL
IsControlActive()
{
    return GetKeyState(VK_CONTROL) < 0;
}

BOOL
IsAltActive()
{
    return GetKeyState(VK_MENU) & 0x8000;
}

BOOL
IsRightArrowActive()
{
    return GetKeyState(VK_RIGHT) < 0;
}

BOOL
IsLeftArrowActive()
{
    return GetKeyState(VK_LEFT) < 0;
}