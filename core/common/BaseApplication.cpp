#include "BaseApplication.hpp"

namespace Lumi{

int BaseApplication::initialize() {
    _quit = false;
    return 0;
}

void BaseApplication::finalize() {

}

void BaseApplication::tick() {

}

bool BaseApplication::isQuit() {
    return _quit;
}

};