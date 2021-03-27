/**
 * @file       functions.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-06
 * 
 * @brief    Utility functions in math library.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <cmath>

namespace lumi {

template <typename T>
inline T Abs(const T val) {
    return val < 0 ? -val : val;
}

template <typename T>
inline bool IsZero(const T val) {
    return val == 0;
}

template <>
inline bool IsZero(const float val) {
    return Abs(val) < 1e-5f;
}

template <>
inline bool IsZero(const double val) {
    return Abs(val) < 1e-10;
}

template <typename T>
inline float Sqrt(const T val) {
    return std::sqrt(static_cast<float>(val));
}

}; ///< namespace lumi
