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

#include "core/BaseApplication.h"
#include <iostream>

bool Lumi::BaseApplication::_quit = false;

int Lumi::BaseApplication::Initialize() {
    _quit = false;
    std::cout << _config;
    return 0;
}

void Lumi::BaseApplication::Finalize() {}

void Lumi::BaseApplication::Tick() {}

bool Lumi::BaseApplication::IsQuit() { return _quit; }
