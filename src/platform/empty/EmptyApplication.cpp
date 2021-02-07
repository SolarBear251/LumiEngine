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

namespace Lumi {
    Config config;
    BaseApplication BaseApp(config);
    IApplication *App = &BaseApp;

}; ///< namespace Lumi