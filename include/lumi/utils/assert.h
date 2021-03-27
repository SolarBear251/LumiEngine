/**
 * @file       assert.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-03-26
 * 
 * @brief    Assert methods
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <lumi/utils/log.h>

namespace lumi {

#ifdef ENABLE_ASSERT
#define Assert(expression, ...)                                               \
    do {                                                                      \
        ((!!(expression)) ||                                                  \
         (__Assert(#expression, __LINE__, __FILE__, __func__, ##__VA_ARGS__), \
          0));                                                                \
    } while (0)
#else
#define Assert(expression, ...)
#endif

/// ================== Assert fail ======================

template <typename... Args>
inline void __Assert(const char* exp, int line, const char* file,
                     const char* func, Args&&... args) {
    __LogError(line, file, func, "Assert expression (", exp,  ") failed!",
               std::forward<Args>(args)...);
    abort();
}

}; ///< namespace lumi