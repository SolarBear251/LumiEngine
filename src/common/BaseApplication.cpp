/**
 * @file       BaseApplication.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Methods definitions for BaseApplication
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include "BaseApplication.h"

namespace Lumi {

int BaseApplication::Initialize() {
    _quit = false;
    return 0;
}

void BaseApplication::Finalize() {

}

void BaseApplication::Tick() {

}

bool BaseApplication::IsQuit() {
    return _quit;
}

}; ///< namespace Lumi