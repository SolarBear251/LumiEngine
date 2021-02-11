/**
 * @file       Config.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-08
 * 
 * @brief    Global configuration of the engine
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include "core/Config.h"

namespace Lumi {

/// Global runtime modules
IApplication*   gApp;
AssetLoader*    gAssetLoader;

}; ///< namespace Lumi

void Lumi::Config::Finalize() {
    delete gApp;
    delete gAssetLoader;
}