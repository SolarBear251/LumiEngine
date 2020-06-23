#include "BaseApplication.hpp"

namespace Lumi {
    BaseApplication g_App;
    IApplication *g_pApp = &g_App;
};