#include <iostream>
#include "IApplication.hpp"

namespace Lumi {
    extern IApplication *g_pApp;
}

int main(int argc, char **argv) {
    int ret;
    if((ret = Lumi::g_pApp->initialize()) != 0) {
        std::cout << "App initialize failed. Exit now" << std::endl;
        return ret;
    }

    while(!Lumi::g_pApp->isQuit()) {
        Lumi::g_pApp->tick();
    }

    Lumi::g_pApp->finalize();

    return 0;
}