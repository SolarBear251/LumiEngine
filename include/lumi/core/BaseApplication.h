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

#include <lumi/interface/IApplication.h>

namespace lumi {

class BaseApplication : implements IApplication {
protected:
    static bool _quit;

public:
    /// Constructors and destructors
    BaseApplication() = default;
    virtual ~BaseApplication() {}

    /// Override functions
    virtual int Initialize() override;
    virtual void Finalize() override;
    virtual void Tick() override;
    virtual bool IsQuit() override;


}; ///< class BaseApplication

}; ///< namespace lumi