#ifdef WIN32
#   include <win.h>
int
WINAPI
wWinMain(
        _In_        HINSTANCE hInstance,
        _In_opt_    HINSTANCE hPrevInstance,
        _In_        PWSTR pCmdLine,
        _In_        int nCmdShow
)
#else
#   include <linux.h>
int
main(int argc, char** argv)
#endif//WIN32
{
    Start();
}