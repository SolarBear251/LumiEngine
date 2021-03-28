/**
 * @file       ispc.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-06
 * 
 * @brief    Declarations of ispc math operations.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <cstdint>
#include <type_traits>

namespace lumi {

#define __DECLARE_FOR_SIGNED(DECLARE) \
    DECLARE(float, float);            \
    DECLARE(double, double);          \
    DECLARE(int32_t, int32);

#define __DECLARE_FOR_UNSIGNED(DECLARE) \
    DECLARE(uint8_t, uint8)

#define __DECLARE_FOR_EACH_TYPE(DECLARE) \
    __DECLARE_FOR_SIGNED(DECLARE);       \
    __DECLARE_FOR_UNSIGNED(DECLARE)


#ifdef USE_ISPC
/// ===================== ispc declarations =======================
namespace ispc {
extern "C" {

#define __ISPC_DECLARATIONS(T, ispcType)                                   \
    T Sum_##ispcType(const T *data, const size_t cnt);                     \
    T SquareSum_##ispcType(const T *data, const size_t cnt);               \
    void Negate_##ispcType(T *res, const size_t cnt);                      \
    void Abs_##ispcType(T *data, const size_t cnt);                        \
    void MulNumber_##ispcType(T *data, const float num, const size_t cnt); \
    void AddByElement_##ispcType(T *res, const T *a, const T *b,           \
                                 const size_t cnt);                        \
    void SubByElement_##ispcType(T *res, const T *a, const T *b,           \
                                 const size_t cnt);                        \
    void MulByElement_##ispcType(T *res, const T *a, const T *b,           \
                                 const size_t cnt);                        \
    void Cross3_##ispcType(T *res, const T *a, const T *b)

__DECLARE_FOR_EACH_TYPE(__ISPC_DECLARATIONS);

    //                                                                           \
    // /* ===================== Matrix ======================= */                \
    //                                                                           \
    // /**                                                                       \
    //  * @brief    Transform the input vector by the input matrix.              \
    //  *                                                                        \
    //  * @param    v           Input and result vector                          \
    //  * @param    m           Input matrix                                     \
    //  *                                                                        \
    //  */                                                                       \
    // void Transform(T v[4], const T m[16]);                                    \
    //                                                                           \
    // /**                                                                       \
    //  * @brief    Transpose the input matrix.                                  \
    //  *                                                                        \
    //  * @param    res         Result matrix                                    \
    //  * @param    m           Input matrix                                     \
    //  * @param    rows        Rows count                                       \
    //  * @param    cols        Columns count                                    \
    //  *                                                                        \
    //  */                                                                       \
    // void Transpose(T *res, const T *m, const size_t rows, const size_t cols); \
    //                                                                           \
    // /**                                                                       \
    //  * @brief    Set input matrix to identity.                                \
    //  *                                                                        \
    //  * @param    data        Input and result matrix.                         \
    //  * @param    n           Dimension of the matrix.                         \
    //  *                                                                        \
    //  */                                                                       \
    // void SetIdentity(T *data, const size_t n);                                \
    //                                                                           \
    // /**                                                                       \
    //  * @brief    Inverse the 3x3 Matrix.                                      \
    //  *                                                                        \
    //  *                                                                        \
    //  * @param    m           Input and result matrix                          \
    //  *                                                                        \
    //  * @return   true        Success                                          \
    //  * @return   false       Failure                                          \
    //  */                                                                       \
    // bool InvMat3x3f(float m[9]);                                              \
    //                                                                           \
    // /**                                                                       \
    //  * @brief    Inverse the 4x4 Matrix.                                      \
    //  *                                                                        \
    //  *                                                                        \
    //  * @param    m           Input and result matrix                          \
    //  *                                                                        \
    //  * @return   true        Success                                          \
    //  * @return   false       Failure                                          \
    //  */                                                                       \
    // bool InvMat4x4f(float m[16])

}; ///< extern "C"
}; ///< namespace ispc
#endif



/// ===================== Inline methods =======================

/**
 * @brief    Get the sum of each value in the array
 *
 * @param    data        Pointer to the array
 * @param    cnt         Array size
 *
 * @return   T           Sum of each value in the array
 */
#ifdef USE_ISPC
#define __SUM_TYPE(T, ispcType)                     \
    inline T Sum(const T *data, const size_t cnt) { \
        return ispc::Sum_##ispcType(data, cnt);     \
    }
#else
#define __SUM_TYPE(T, ispcType)                     \
    inline T Sum(const T *data, const size_t cnt) { \
        T sum = 0;                                  \
        for (size_t i = 0; i < cnt; i++) {          \
            sum += data[i];                         \
        }                                           \
        return sum;                                 \
    }
#endif
__DECLARE_FOR_EACH_TYPE(__SUM_TYPE);

/**
 * @brief    Get the square sum of each value in the array
 *
 * @param    data        Pointer to the array
 * @param    cnt         Array size
 *
 * @return   T           Square sum of each value in the array
 */
#ifdef USE_ISPC
#define __SQUARESUM_TYPE(T, ispcType)                     \
    inline T SquareSum(const T *data, const size_t cnt) { \
        return ispc::SquareSum_##ispcType(data, cnt);     \
    }
#else
#define __SQUARESUM_TYPE(T, ispcType)                     \
    inline T SquareSum(const T *data, const size_t cnt) { \
        T sum = 0;                                        \
        for (size_t i = 0; i < cnt; i++) {                \
            sum += data[i] * data[i];                     \
        }                                                 \
        return sum;                                       \
    }
#endif
__DECLARE_FOR_EACH_TYPE(__SQUARESUM_TYPE);

/**
 * @brief    Negate each value in the array.
 *
 * @param    data        Pointer to the array
 * @param    cnt         Array size
 *
 */
#ifdef USE_ISPC
#define __NEGATE_TYPE(T, ispcType)                  \
    inline void Negate(T *data, const size_t cnt) { \
        ispc::Negate_##ispcType(data, cnt);         \
    }
#else
#define __NEGATE_TYPE(T, ispcType)                  \
    inline void Negate(T *data, const size_t cnt) { \
        for (size_t i = 0; i < cnt; i++) {          \
            data[i] = -data[i];                     \
        }                                           \
    }
#endif
__DECLARE_FOR_EACH_TYPE(__NEGATE_TYPE);

/**
 * @brief    Absolute each value in the array.
 *
 * @param    data        Pointer to the array
 * @param    cnt         Array size
 *
 */
#ifdef USE_ISPC
#define __ABS_TYPE(T, ispcType)                  \
    inline void Abs(T *data, const size_t cnt) { \
        if (std::is_unsigned<T>::value) return;  \
        ispc::Abs_##ispcType(data, cnt);         \
    }
#else
#define __ABS_TYPE(T, ispcType)                         \
    inline void Abs(T *data, const size_t cnt) {        \
        if (std::is_unsigned<T>::value) return;         \
        for (size_t i = 0; i < cnt; i++) {              \
            data[i] = data[i] < 0 ? -data[i] : data[i]; \
        }                                               \
    }
#endif
__DECLARE_FOR_EACH_TYPE(__ABS_TYPE);

/**
 * @brief    Multiply each value in the array by a given number
 *
 * @param    data        Pointer to the array
 * @param    num         Divisor
 * @param    cnt         Array size
 *
 */
#ifdef USE_ISPC
#define __MULNUMBER_TYPE(T, ispcType)                                   \
    inline void MulNumber(T *data, const float num, const size_t cnt) { \
        ispc::MulNumber_##ispcType(data, num, cnt);                     \
    }
#else
#define __MULNUMBER_TYPE(T, ispcType)                                   \
    inline void MulNumber(T *data, const float num, const size_t cnt) { \
        for (size_t i = 0; i < cnt; i++) {                              \
            data[i] = static_cast<T>(num * data[i]);                    \
        }                                                               \
    }
#endif
__DECLARE_FOR_EACH_TYPE(__MULNUMBER_TYPE);

/*
 * @brief    Add two arrays by element.
 *
 * @param    res         Result array
 * @param    a           Left operand array
 * @param    b           Right operand array
 * @param    cnt         Array size
 *
 */
#ifdef USE_ISPC
#define __ADDBYELEMENT_TYPE(T, ispcType)                     \
    inline void AddByElement(T *res, const T *a, const T *b, \
                             const size_t cnt) {             \
        ispc::AddByElement_##ispcType(res, a, b, cnt);       \
    }
#else
#define __ADDBYELEMENT_TYPE(T, ispcType)                     \
    inline void AddByElement(T *res, const T *a, const T *b, \
                             const size_t cnt) {             \
        for (size_t i = 0; i < cnt; i++) {                   \
            res[i] = a[i] + b[i];                            \
        }                                                    \
    }
#endif
__DECLARE_FOR_EACH_TYPE(__ADDBYELEMENT_TYPE);

/*
 * @brief    Subtract two arrays by element.
 *
 * @param    res         Result array
 * @param    a           Left operand array
 * @param    b           Right operand array
 * @param    cnt         Array size
 *
 */
#ifdef USE_ISPC
#define __SUBBYELEMENT_TYPE(T, ispcType)                     \
    inline void SubByElement(T *res, const T *a, const T *b, \
                             const size_t cnt) {             \
        ispc::SubByElement_##ispcType(res, a, b, cnt);       \
    }
#else
#define __SUBBYELEMENT_TYPE(T, ispcType)                     \
    inline void SubByElement(T *res, const T *a, const T *b, \
                             const size_t cnt) {             \
        for (size_t i = 0; i < cnt; i++) {                   \
            res[i] = a[i] - b[i];                            \
        }                                                    \
    }
#endif
__DECLARE_FOR_EACH_TYPE(__SUBBYELEMENT_TYPE);

/*
 * @brief    Multiply two arrays by element.
 *
 * @param    res         Result array
 * @param    a           Left operand array
 * @param    b           Right operand array
 * @param    cnt         Array size
 *
 */
#ifdef USE_ISPC
#define __MULBYELEMENT_TYPE(T, ispcType)                     \
    inline void MulByElement(T *res, const T *a, const T *b, \
                             const size_t cnt) {             \
        ispc::MulByElement_##ispcType(res, a, b, cnt);       \
    }
#else
#define __MULBYELEMENT_TYPE(T, ispcType)                     \
    inline void MulByElement(T *res, const T *a, const T *b, \
                             const size_t cnt) {             \
        for (size_t i = 0; i < cnt; i++) {                   \
            res[i] = a[i] * b[i];                            \
        }                                                    \
    }
#endif
__DECLARE_FOR_EACH_TYPE(__MULBYELEMENT_TYPE);

/**
 * @brief    Cross product of Vec3
 *
 * @param    res         Pointer to result array
 * @param    a           Left operand array
 * @param    b           Right operand array
 *
 */
#ifdef USE_ISPC
#define __CROSS3_TYPE(T, ispcType)                       \
    inline void Cross3(T *res, const T *a, const T *b) { \
        ispc::Cross3_##ispcType(res, a, b);              \
    }
#else
#define __CROSS3_TYPE(T, ispcType)                       \
    inline void Cross3(T *res, const T *a, const T *b) { \
        res[0] = a[1] * b[2] - a[2] * b[1];              \
        res[1] = a[2] * b[0] - a[0] * b[2];              \
        res[2] = a[0] * b[1] - a[1] * b[0];              \
    }
#endif
__DECLARE_FOR_EACH_TYPE(__CROSS3_TYPE);


}; ///< namespace lumi

