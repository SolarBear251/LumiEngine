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

#ifdef USE_ISPC

#include <cstdint>

namespace lumi {

namespace ispc {
extern "C" {

// ===================== Common =======================

/**
 * @brief    Add two number arrays by element.
 *
 * @param    res         Result array
 * @param    a           Left operand array
 * @param    b           Right operand array
 * @param    cnt         Count of involved elements
 *
 */
void AddByElement(float *res, const float *a, const float *b, const size_t cnt);

/**
 * @brief    Substract two number arrays by element.
 *
 * @param    res         Result array
 * @param    a           Left operand array
 * @param    b           Right operand array
 * @param    cnt         Count of involved elements
 *
 */
void SubByElement(float *res, const float *a, const float *b, const size_t cnt);

/**
 * @brief    Multiply two number arrays by element.
 *
 * @param    res         Result array
 * @param    a           Left operand array
 * @param    b           Right operand array
 * @param    cnt         Count of involved elements
 *
 */
void MulByElement(float *res, const float *a, const float *b, const size_t cnt);

/**
 * @brief    Divide two number arrays by element.
 *
 * @param    res         Result array
 * @param    a           Left operand array
 * @param    b           Right operand array
 * @param    cnt         Count of involved elements
 *
 */
void DivByElement(float *res, const float *a, const float *b, const size_t cnt);

/**
 * @brief    Negate each element in number array.
 *
 * @param    res         Result array
 * @param    data        Input array
 * @param    cnt         Count of involved elements
 *
 */
void Negate(float *res, const float *data, const size_t cnt);

/**
 * @brief    Get Absolute value of each element in number array.
 *
 * @param    res         Result array
 * @param    data        Input array
 * @param    cnt         Count of involved elements
 *
 */
void Absolute(float *res, const float *data, const size_t cnt);

/**
 * @brief    Square root of each element in number array.
 *
 * @param    res         Result array
 * @param    data        Input array
 * @param    cnt         Count of involved elements
 *
 */
void Sqrt(float *res, const float *data, const size_t cnt);

/**
 * @brief    Power of each element in number array.
 *
 * @param    res         Result array
 * @param    data        Input array
 * @param    cnt         Count of involved elements
 * @param    exponent    The exponent of the power
 *
 */
void Power(float *res, const float *data, const size_t cnt,
           const float exponent);

// ===================== Vector =======================

/**
 * @brief    Cross Product of 3D Vectors.
 *
 * @param    res         Result array
 * @param    a           Left operand array
 * @param    b           Right operand array
 *
 */
void Cross3(float res[3], const float a[3], const float b[3]);

// ===================== Matrix =======================

/**
 * @brief    Transform the input vector by the input matrix.
 *
 * @param    v           Input and result vector
 * @param    m           Input matrix
 *
 */
void Transform(float v[4], const float m[16]);

/**
 * @brief    Transpose the input matrix.
 *
 * @param    res         Result matrix
 * @param    m           Input matrix
 * @param    rows        Rows count
 * @param    cols        Columns count
 *
 */
void Transpose(float *res, const float *m, const uint32_t rows,
               const uint32_t cols);

/**
 * @brief    Set input matrix to identity.
 * 
 * @param    data        Input and result matrix.
 * @param    n           Dimension of the matrix.
 * 
 */
void SetIdentity(float *data, const int32_t n);

/**
 * @brief    Inverse the 3x3 Matrix.
 * 
 * 
 * @param    m           Input and result matrix
 * 
 * @return   true        Success
 * @return   false       Failure
 */
bool InvMat3x3f(float m[9]);

/**
 * @brief    Inverse the 4x4 Matrix.
 *
 *
 * @param    m           Input and result matrix
 *
 * @return   true        Success
 * @return   false       Failure
 */
bool InvMat4x4f(float m[16]);


}; ///< extern "C"
}; ///< namespace ispc

}; ///< namespace lumi

#endif
