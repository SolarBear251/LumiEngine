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

#include "BaseApplication.h"

namespace Lumi {
    BaseApplication BaseApp;
    IApplication *App = &BaseApp;

}; ///< namespace Lumi