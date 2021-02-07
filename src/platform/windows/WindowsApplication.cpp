/**
 * @file       WindowsApplication.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-07
 *
 * @brief    Methods definitions for WindowsApplication
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

#include "platform/windows/WindowsApplication.h"

namespace Lumi {
    Config Conf("LumiEngine", 960, 540, 8, 8, 8, 8, 32, 0, 0);
    WindowsApplication WindowsApp(Conf);
    IApplication *App = &WindowsApp;

}; ///< namespace Lumi

int Lumi::WindowsApplication::Initialize() {
    // Init base application
    int result = BaseApplication::Initialize();
    if (result != 0) exit(result);

    // HINSTANCE of the console program
    HINSTANCE hInstance = GetModuleHandle(NULL);
    // Handle for the window
    HWND hWnd;
    // Information for the window class
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "LumiEngine";

    // Register the windows class
    RegisterClassEx(&wc);
    // Create the window and use the result as the handle
    hWnd = CreateWindowEx(0,
                          "LumiEngine",           ///< name of the window class
                          _config._appName,       ///< title of the window
                          WS_OVERLAPPEDWINDOW,    ///< window style
                          CW_USEDEFAULT,          ///< x-position of the window
                          CW_USEDEFAULT,          ///< y-position of the window
                          _config._screenWidth,   ///< width of the window
                          _config._screenHeight,  ///< height of the window
                          NULL,                   ///< parent window
                          NULL,                   ///< menus
                          hInstance,              ///< application handle
                          this                    ///< pass pointer to current object
    );
    // Display the window
    ShowWindow(hWnd, SW_SHOW);
    _hWnd = hWnd;

    return result;
}

void Lumi::WindowsApplication::Finalize() {


}

void Lumi::WindowsApplication::Tick() {
    // Windows event message
    MSG msg;
    // Use PeekMessage instead of GetMessage here
    // because we should not block the thread at anywhere
    // except the engine execution driver module
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        // Translate message into right format
        TranslateMessage(&msg);
        // Send the message to WindowProc
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK Lumi::WindowsApplication::WindowProc(HWND hWnd, UINT message,
                                                      WPARAM wParam,
                                                      LPARAM lParam) {
    // Get Application object
    WindowsApplication *app;
    if (message == WM_NCCREATE) {
        app = reinterpret_cast<WindowsApplication *>(
            reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams);
    } else {
        app = reinterpret_cast<WindowsApplication *>(
            GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    // Check the message
    if (message == WM_PAINT) {
        // app->OnDraw();
    } else if (message == WM_KEYDOWN) {
        // TODO: replace with input manager
        _quit = true;
    } else if (message == WM_DESTROY) {
        // The window is closed, close the application
        PostQuitMessage(0);
        _quit = true;
        return 0;
    }

    // Handle the message not catched above
    return DefWindowProc(hWnd, message, wParam, lParam);
}