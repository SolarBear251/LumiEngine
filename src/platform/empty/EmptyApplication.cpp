/**
 * @file       EmptyApplication.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Application for empty platform.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include "core/BaseApplication.h"
#include "core/Config.h"

Lumi::IApplication* Lumi::Config::GetInitApp() {
    static BaseApplication baseApp;
    return &baseApp;
}