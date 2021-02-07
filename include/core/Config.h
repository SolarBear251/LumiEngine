/**
 * @file       Config.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-07
 * 
 * @brief    Configuration of the engine
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <iostream>
#include <cstdint>

namespace Lumi {

struct Config {
    const char* _appName;
    uint32_t _screenWidth;
    uint32_t _screenHeight;

    uint32_t _redBits;      ///< red   color channel depth in bits
    uint32_t _greenBits;    ///< green color channel depth in bits
    uint32_t _blueBits;     ///< blue  color channel depth in bits
    uint32_t _alphaBits;    ///< alpha color channel depth in bits

    uint32_t _depthBits;    ///< depth buffer depth in bits
    uint32_t _stencilBits;  ///< stencil buffer depth in bits
    uint32_t _msaaSamples;  ///< MSAA samples

    /// Constructors
    Config(const char* app_name = "LumiEngine", uint32_t width = 1920,
           uint32_t height = 1080, uint32_t r = 8, uint32_t g = 8,
           uint32_t b = 8, uint32_t a = 8, uint32_t d = 24, uint32_t s = 0,
           uint32_t msaa = 0)
        : _appName(app_name),
          _screenWidth(width),
          _screenHeight(height),
          _redBits(r),
          _greenBits(g),
          _blueBits(b),
          _alphaBits(a),
          _depthBits(d),
          _stencilBits(s),
          _msaaSamples(msaa)

    {}

}; ///< struct Config

inline std::ostream& operator<<(std::ostream& out, const Config& config) {
    out << "App name: " << config._appName << ", " 
        << config._screenWidth << "x"
        << config._screenHeight << std::endl
        << "R: " << config._redBits     << ", "
        << "G: " << config._greenBits   << ", "
        << "B: " << config._blueBits    << ", "
        << "A: " << config._alphaBits   << ", "
        << "D: " << config._depthBits   << ", "
        << "S: " << config._stencilBits << ", "
        << "M: " << config._msaaSamples << std::endl;

    return out;
}

}; ///< namespace Lumi
