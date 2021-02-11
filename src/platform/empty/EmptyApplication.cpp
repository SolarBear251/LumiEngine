/**
 * @file       EmptyApplication.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Application for empty platform.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include "core/Config.h"
#include "core/BaseApplication.h"

int Lumi::Config::InitByPlatform() {
    gApp         = new BaseApplication();
    gAssetLoader = new AssetLoader();
    return 0;
}
