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

#include <lumi/core/Config.h>

namespace lumi {

/// Global runtime modules
IApplication*   gApp;
AssetLoader*    gAssetLoader;

}; ///< namespace lumi

void lumi::Config::Finalize() {
    delete gApp;
    delete gAssetLoader;
}