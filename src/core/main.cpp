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

#include <lumi/core/Config.h>

#include <iostream>

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
    int res = lumi::Config::Instance().Initialize();
    if (res != 0) {
        std::cerr << "Config failed." << std::endl;
        return EXIT_FAILURE;
    }
    // Initialize modules
    std::vector<lumi::IRuntimeModule*> modules;
    modules.emplace_back(lumi::gApp);
    modules.emplace_back(lumi::gAssetLoader);
    for (auto &module : modules) {
        if ((res = module->Initialize()) != 0) {
            std::cerr << "Initialize failed, err = " << res << std::endl;
            return EXIT_FAILURE;
        }
    }
    // Tick
    while(!lumi::gApp->IsQuit()) {
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