/**
 * @file       main.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Entry of the engine.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include <iostream>

#include "interface/IApplication.h"
#include "core/Config.h"
#include "core/AssetLoader.h"

/**
 * @brief    Main function. Entry of the engine.
 * 
 * @param    argc        Argument count.
 * @param    argv        Argument values.
 * 
 * @return   int        Exit status of the program.
 */
int main(int argc, char **argv) {
    // Config modules
    Lumi::Config::Instance().Initialize();
    std::vector<Lumi::IRuntimeModule*> modules;
    modules.emplace_back(Lumi::gApp);
    modules.emplace_back(Lumi::gAssetLoader);

    // Initialize modules
    int res;
    for (auto &module : modules) {
        if ((res = module->Initialize()) != 0) {
            std::cerr << "Initialize failed, err = " << res << std::endl;
            return EXIT_FAILURE;
        }
    }
    // Tick
    while(!Lumi::gApp->IsQuit()) {
        for (auto &module : modules) {
            module->Tick();
        }
    }
    // Finalize
    for (auto &module : modules) {
        module->Finalize();
    }

    return EXIT_SUCCESS;
}