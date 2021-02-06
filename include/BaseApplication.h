/**
 * @file       BaseApplication.hpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Header for BaseApplication
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include "interface/IApplication.h"

namespace Lumi {

class BaseApplication : implements IApplication {
public:
    virtual ~BaseApplication() {}

    virtual int Initialize() override;
    virtual void Finalize() override;

    virtual void Tick() override;

    virtual bool IsQuit() override;

protected:
    bool _quit;

}; ///< class BaseApplication

}; ///< namespace Lumi