#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Windows program entry
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    // handle for the window
    HWND hWnd;
    // infomation for window
    WNDCLASSEX wc;
    // clear window class
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill needed infomation
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");
    // register the window class
    RegisterClassEx(&wc);

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(
        0,
        _T("WindowClass1"), // name of window class
        _T("Hello, Engine!"), // title
        WS_OVERLAPPEDWINDOW, // window style
        300,    // x-position
        300,    // y-position
        500,    // width
        400,    // height
        NULL,   // parent window
        NULL,   // menus
        hInstance, // application handle
        NULL    // used with multiple windows
    );
    ShowWindow(hWnd, nCmdShow);

    // main loop
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        // translate keystroke messages into right format
        TranslateMessage(&msg);
        // send the message to WindowProc function
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// main message handler
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rec = { 20, 20, 60, 80};
            HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);

            FillRect(hdc, &rec, brush);

            EndPaint(hWnd, &ps);
        } break;
        case WM_DESTROY:
        {
            // close the application
            PostQuitMessage(0);
            return 0;
        } break;
    }

    // default message handler
    return DefWindowProc(hWnd, message, wParam, lParam);
}