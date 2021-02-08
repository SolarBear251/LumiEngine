/**
 * @file       WindowsApplication.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-07
 * 
 * @brief    Header for windows application
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include "core/BaseApplication.h"
#include <windows.h>
#include <windowsx.h>

namespace Lumi {

class WindowsApplication : public BaseApplication {
private:
    HWND _hWnd;

public:
    /// Constructors and destructors
    using BaseApplication::BaseApplication;
    virtual ~WindowsApplication() {}

    /// Override functions
    virtual int Initialize() override;
    virtual void Finalize() override;
    virtual void Tick() override;

    /// Getters
    HWND GetMainWindow() const { return _hWnd; }

private:
    /**
     * @brief    Main message handler for the program.
     * 
     * @param    hWnd        Handle of the window
     * @param    message     Message from the window
     * @param    wParam      Additional message
     * @param    lParam      Additional message
     * 
     * @return   LRESULT     Result code
     */
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,
                                       LPARAM lParam);
};


}; ///< namespace Lumi