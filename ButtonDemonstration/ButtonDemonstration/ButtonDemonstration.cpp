// Compile With gcc window.c -o window.exe -lgdi32
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <tchar.h>
const TCHAR CLSNAME[] = TEXT("helloworldWClass");
LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp);

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR cmdline, int cmdshow)
{
    WNDCLASSEX wc;
    MSG msg;
    HWND hwnd;

    wc.cbSize = sizeof(wc);
    wc.style = 0;
    wc.lpfnWndProc = winproc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_PEN);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = CLSNAME;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, TEXT("Could not register window class"),
            NULL, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindowExW(WS_EX_LEFT,
        CLSNAME,
        NULL,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInst,
        NULL);
    if (!hwnd) {
        MessageBox(NULL, TEXT("Could not create window"), NULL, MB_ICONERROR);
        return 0;
    }

    HWND hwndBtnOne = CreateWindowW(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"One",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        580,         // x position 
        470,         // y position 
        100,        // Button width
        100,        // Button height
        hwnd,     // Parent window
        (HMENU)1,       // No menu.
        hInst,
        NULL);      // Pointer not needed.

    HWND hwndBtnTwo = CreateWindowW(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Two",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        700,         // x position 
        470,         // y position 
        100,        // Button width
        100,        // Button height
        hwnd,     // Parent window
        (HMENU)2,       // No menu.
        hInst,
        NULL);      // Pointer not needed.

    HWND hwndBtnQuit = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Quit",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        640,         // x position 
        580,         // y position 
        100,        // Button width
        100,        // Button height
        hwnd,     // Parent window
        (HMENU)3,       // No menu.
        hInst,
        NULL);      // Pointer not needed.

    HWND hwndExample = CreateWindow(
        L"STATIC", 
        L"Text Goes Here", 
        WS_VISIBLE | WS_CHILD | SS_CENTER,  // will probably need SS_OWNERDRAW. the owner window recieves a WM_DRAWITEM whenever the control needs to be drawn 
        440, 
        50, 
        500, 
        200, 
        hwnd, 
        (HMENU)4,
        hInst, 
        NULL);

    ShowWindow(hwnd, cmdshow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp)
{
    if (wm == WM_DESTROY) {
        PostQuitMessage(0);
    } if (wm == WM_COMMAND) {
        if (HIWORD(wp) == BN_CLICKED && LOWORD(wp) == 1) {
            MessageBox(hwnd, L"You clicked ONE", L"BN_CLICKED", MB_ICONINFORMATION);
        }
        else if (HIWORD(wp) == BN_CLICKED && LOWORD(wp) == 2) {
            MessageBox(hwnd, L"You clicked TWO", L"BN_CLICKED", MB_ICONINFORMATION);
        }
        else if (HIWORD(wp) == BN_CLICKED && LOWORD(wp) == 3) {
            PostQuitMessage(0);
        }
    }
    return DefWindowProc(hwnd, wm, wp, lp);
}