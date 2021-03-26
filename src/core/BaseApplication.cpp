/**
 * @file       BaseApplication.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Methods definitions of BaseApplication
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include <lumi/core/BaseApplication.h>
#include <lumi/core/Config.h>

#include <iostream>

bool lumi::BaseApplication::_quit = false;

int lumi::BaseApplication::Initialize() {
    _quit = false;
    std::cout << Config::Instance();
    return 0;
}

void lumi::BaseApplication::Finalize() {}

void lumi::BaseApplication::Tick() {}

bool lumi::BaseApplication::IsQuit() { return _quit; }
