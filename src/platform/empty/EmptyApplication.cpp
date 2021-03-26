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

#include <lumi/core/BaseApplication.h>
#include <lumi/core/Config.h>

int lumi::Config::InitByPlatform() {
    gApp         = new BaseApplication();
    gAssetLoader = new AssetLoader();
    return 0;
}
