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
#include "Config.h"

namespace Lumi {

class BaseApplication : implements IApplication {
protected:
    static bool _quit;
    Config _config;

public:
    /// Constructors and destructors
    BaseApplication() = delete;     ///< Enforce a configuration
    BaseApplication(Config &config) : _config(config) {}
    virtual ~BaseApplication() {}

    /// Override functions
    virtual int Initialize() override;
    virtual void Finalize() override;
    virtual void Tick() override;
    virtual bool IsQuit() override;


}; ///< class BaseApplication

}; ///< namespace Lumi