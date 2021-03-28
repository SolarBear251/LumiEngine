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
    // Config
    int res = lumi::Config::Instance().Initialize();
    if (res != 0) {
        std::cerr << "Config failed." << std::endl;
        return EXIT_FAILURE;
    }

    // Modules. Pay attention to the order!
    std::vector<lumi::IRuntimeModule*> modules;
    modules.emplace_back(lumi::gApp);
    modules.emplace_back(lumi::gAssetLoader);

    // Initialize
    for (auto it = modules.begin(); it != modules.end(); ++it) {
        if ((res = (*it)->Initialize()) != 0) {
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
    for (auto it = modules.rbegin(); it != modules.rend(); ++it) {
        (*it)->Finalize();
    }

    return EXIT_SUCCESS;
}