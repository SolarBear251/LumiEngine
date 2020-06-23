#pragma once

#include "IRuntimeModule.hpp"

namespace Lumi{

interface IApplication: implements IRuntimeModule
{
public:
    virtual ~IApplication() { }

    virtual int initialize() = 0;
    virtual void finalize() = 0;

    virtual void tick() = 0;

    virtual bool isQuit() = 0;
};

};