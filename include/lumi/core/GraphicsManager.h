/**
 * @file       GraphicsManager.hpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Graphics module manager.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <lumi/interface/IRuntimeModule.h>

namespace lumi {

class GraphicsManager: implements IRuntimeModule 
{
public:
    virtual ~GraphicsManager() = default;

    /// Override functions
    virtual int Initialize() override;
    virtual void Finalize() override;
    virtual void Tick() override;

    /**
     * @brief    Render current frame
     * 
     */
    virtual void Render();

}; ///< class GraphicsManager

}; ///< namespace lumi