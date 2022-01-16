#include <mediakeys.h>

#ifdef WIN32

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

#else

int
main(int argc, char** argv)
{
    int i = 0;
    for (;;)
    {
        /* Previous */
        if (IsControlComboActive() && IsKeyActive(XK_Left))
            SimulateKeyPress(XK_Prior);

        /* Next */
        if (IsControlComboActive() && IsKeyActive(XK_Right))
            SimulateKeyPress(XK_Next);

        /* Pause */
        if (IsControlComboActive() && IsKeyActive(XK_space))
        {
            printf("Pause %d\n", i);
            i++;
            //SimulateKeyPress(XK_Pause);
        }
    }
}

Bool
IsControlComboActive()
{
    return IsKeyActive(XK_Control_L) && IsKeyActive(XK_Alt_L);
}

void
SimulateKeyPress(KeySym keysym)
{
    /* Open connection to X server */
    Display* display = XOpenDisplay(NULL);

    /* Get keycode */
    KeyCode keycode = XKeysymToKeycode(display, keysym);

    /* Simulate key press */
    XTestFakeKeyEvent(display, keycode, True, 0);
    XTestFakeKeyEvent(display, keycode, False, 0);

    /* Close connection to X server */
    XFlush(display);
}

Bool
IsKeyActive(KeySym keysym)
{
    /* Open connection to X server */
    Display* display = XOpenDisplay(NULL);

    if (display == NULL)
        return(False);

    KeyCode keycode = XKeysymToKeycode(display, keysym);
    if (keycode == 0)
    {
        /* Close the connection with the X server */
        XCloseDisplay(display);
        return(False);
    }

    /* Get the whole keyboard state */
    char keys[32];
    XQueryKeymap(display, keys);

    /* Close the connection with the X server */
    XCloseDisplay(display);

    /* Check keycode */
    return (keys[keycode / 8] & (1 << (keycode % 8))) != 0;
}

#endif //!WIN32