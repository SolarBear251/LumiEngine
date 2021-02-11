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

#include "core/Config.h"

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
    int res = Lumi::Config::Instance().Initialize();
    if (res != 0) {
        std::cerr << "Config failed." << std::endl;
        return EXIT_FAILURE;
    }
    // Initialize modules
    std::vector<Lumi::IRuntimeModule*> modules;
    modules.emplace_back(Lumi::gApp);
    modules.emplace_back(Lumi::gAssetLoader);
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