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
#include "core/AssetLoader.h"
#include "interface/IApplication.h"

namespace Lumi {

/// Global runtime modules
IApplication*   gApp;
AssetLoader*    gAssetLoader;

}; ///< namespace Lumi

int Lumi::Config::Initialize() {
    gApp         = GetInitApp();
    gAssetLoader = new AssetLoader();

    return 0;
}

void Lumi::Config::Finalize() {
    delete gAssetLoader;
}