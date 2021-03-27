/**
 * @file       log.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-03-26
 * 
 * @brief    Log methods
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <iostream>

namespace lumi {

/// Use macros to get __LINE__, __FILE__ and __func__
#define LogInfo(...) __LogInfo(__LINE__, __FILE__, __func__, ##__VA_ARGS__)
#define LogError(...) __LogError(__LINE__, __FILE__, __func__, ##__VA_ARGS__)

/// =================== Log Info ======================

template <typename Arg>
inline void __LogInfo_R(Arg&& arg) {
    std::cout << ' ' << std::forward<Arg>(arg);
}

template <typename Arg, typename... Args>
inline void __LogInfo_R(Arg&& arg, Args&&... args) {
    std::cout << ' ' << std::forward<Arg>(arg);
    __LogInfo_R(std::forward<Args>(args)...);
}

template <typename... Args>
inline void __LogInfo(int line, const char* file, const char* func,
                      Args&&... args) {
    std::cout << "INFO  === " << file << ", line " << line << ", " << func
              << "():" << std::endl
              << "      ===";
    __LogInfo_R(std::forward<Args>(args)...);
    std::cout << std::endl;
}

/// =================== Log Error ======================

template <typename Arg>
inline void __LogError_R(Arg&& arg) {
    std::cerr << ' ' << std::forward<Arg>(arg);
}

template <typename Arg, typename... Args>
inline void __LogError_R(Arg&& arg, Args&&... args) {
    std::cerr << ' ' << std::forward<Arg>(arg);
    __LogError_R(std::forward<Args>(args)...);
}

template <typename... Args>
inline void __LogError(int line, const char* file, const char* func,
                       Args&&... args) {
    std::cerr << "ERROR === " << file << ", line " << line << ", " << func
              << "():" << std::endl
              << "      ===";
    __LogError_R(std::forward<Args>(args)...);
    std::cerr << std::endl;
}

}; ///< namespace lumi