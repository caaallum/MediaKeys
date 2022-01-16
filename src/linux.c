#include <linux.h>

void Start()
{
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
            SimulateKeyPress(XK_Pause);
    }
}

Bool IsControlComboActive()
{
    return IsKeyActive(XK_Control_L) && IsKeyActive(XK_Alt_L);
}

void SimulateKeyPress(KeySym keysym)
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

Bool IsKeyActive(KeySym keysym)
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