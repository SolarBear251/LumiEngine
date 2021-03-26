/**
 * @file       IRuntimeModule.hpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Interface for runtime module.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <lumi/interface/Interface.h>

namespace lumi {

interface IRuntimeModule {
public:
    virtual ~IRuntimeModule() { }

    /// Initialize this module
    virtual int Initialize() = 0;
    /// Finalize this module
    virtual void Finalize() = 0;
    /// One cycle of the main loop
    virtual void Tick() = 0;

}; ///< interface IRuntimeModule

}; ///< namespace lumi