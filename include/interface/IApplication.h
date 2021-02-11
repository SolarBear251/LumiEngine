/**
 * @file       IApplication.hpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Interface for application.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include "IRuntimeModule.h"

namespace Lumi {

interface IApplication: implements IRuntimeModule
{
public:
    virtual ~IApplication() { }

    virtual int Initialize() override = 0;
    virtual void Finalize() override = 0;
    virtual void Tick() override = 0;

    /// Whether the application needs to quit
    virtual bool IsQuit() = 0;

}; ///< interface IApplication

extern IApplication* gApp;

}; ///< namespace Lumi