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

namespace Lumi {
    /// External instance of application
    extern IApplication *App;

}; ///< namespace Lumi

/**
 * @brief    Main function. Entry of the engine.
 * 
 * @param    argc        Argument count.
 * @param    argv        Argument values.
 * 
 * @return   int        Exit status of the program.
 */
int main(int argc, char **argv) {
    int ret;

    // Initialize
    if((ret = Lumi::App->Initialize()) != 0) {
        std::cout << "App initialize failed. Exit now" << std::endl;
        return ret;
    }
    // Tick
    while(!Lumi::App->IsQuit()) {
        Lumi::App->Tick();
    }
    // Finalize
    Lumi::App->Finalize();

    return 0;
}