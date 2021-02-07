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

#include "interface/IRuntimeModule.h"

namespace Lumi {

class GraphicsManager: implements IRuntimeModule 
{
public:
    virtual ~GraphicsManager() { }

}; ///< class GraphicsManager

}; ///< namespace Lumi