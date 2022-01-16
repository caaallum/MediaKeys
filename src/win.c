#include <win.h>

void Start()
{
    g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (g_hook == NULL)
    {
        MessageBox(NULL, L"Failed to set windows hook", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return EXIT_FAILURE;
    }

    while (GetMessage(NULL, NULL, 0, 0));

    UnhookWindowsHookEx(g_hook);

    return EXIT_SUCCESS;
}

LRESULT
CALLBACK
KeyboardProc(
        int     nCode,
        WPARAM  wParam,
        LPARAM  lParam
)
{
    INPUT input = { 0 };
    if (wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* hs = (KBDLLHOOKSTRUCT*)lParam;

        /* Next song */
        if (IsControlComboActive() && hs->vkCode == VK_RIGHT)
        {
            input.type      = INPUT_KEYBOARD;
            input.ki.wVk    = VK_MEDIA_NEXT_TRACK;
        }

        /* Previous song */
        if (IsControlComboActive() && hs->vkCode == VK_LEFT)
        {
            input.type      = INPUT_KEYBOARD;
            input.ki.wVk    = VK_MEDIA_PREV_TRACK;
        }

        /* Pause/Play */
        if (IsControlComboActive() && hs->vkCode == VK_SPACE)
        {
            input.type      = INPUT_KEYBOARD;
            input.ki.wVk    = VK_MEDIA_PLAY_PAUSE;
        }

        /* Volume Up */
        if (IsControlComboActive() && hs->vkCode == VK_OEM_PLUS)
        {
            input.type      = INPUT_KEYBOARD;
            input.ki.wVk    = VK_VOLUME_UP;
        }

        /* Volume Down */
        if (IsControlComboActive() && hs->vkCode == VK_OEM_MINUS)
        {
            input.type      = INPUT_KEYBOARD;
            input.ki.wVk    = VK_VOLUME_DOWN;
        }

        UINT uSend = SendInput(1, &input, sizeof(INPUT));

        if (uSend != 1)
            OutputDebugString(L"Failed to send input");
    }
    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

BOOL
IsControlComboActive()
{
    return GetKeyState(VK_CONTROL) < 0 && GetKeyState(VK_MENU) & 0x8000;
}