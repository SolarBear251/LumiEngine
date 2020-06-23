#pragma once

#include "IApplication.hpp"

namespace Lumi {

class BaseApplication : implements IApplication {
public:
    virtual ~BaseApplication() {}

    virtual int initialize();
    virtual void finalize();

    virtual void tick();

    virtual bool isQuit();

protected:
    bool _quit;
};

}; // namespace Lumi