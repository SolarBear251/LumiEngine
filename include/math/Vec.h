/**
 * @file       Vec.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    2D, 3D and 4D vectors.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include "Ispc.h"

#include <initializer_list>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <cmath>

namespace Lumi {

/// Macro for vector member functions
#define __DECLARE_VEC_MEM_FUNC(N)                                       \
   public:                                                              \
    /* Constructors */                                                  \
    Vec##N() = default;                                                 \
    explicit Vec##N(const T val) { Set(val); }                          \
    Vec##N(const Vec##N& v) { Set(v); }                                 \
    Vec##N(std::initializer_list<const T> list) { Set(list); }          \
                                                                        \
    /* Setters */                                                       \
    void Set(const T val) {                                             \
        for (auto& v : data) v = val;                                   \
    }                                                                   \
    void Set(const T* pval) { std::memcpy(data, pval, sizeof(T) * N); } \
    void Set(const Vec##N& v) { std::memcpy(this, &v, sizeof(v)); }     \
    void Set(std::initializer_list<const T> list) {                     \
        assert(list.size() <= N);                                       \
        size_t i = 0;                                                   \
        for (auto& val : list) {                                        \
            data[i++] = val;                                            \
        }                                                               \
        while (i < N) {                                                 \
            data[i++] = 0;                                              \
        }                                                               \
    }                                                                   \
                                                                        \
    T Sum() const {                                                     \
        T res = 0;                                                      \
        for (const auto& val : data) {                                  \
            res += val;                                                 \
        }                                                               \
        return res;                                                     \
    }                                                                   \
                                                                        \
    T Len() const { return Length(*this); }                             \
                                                                        \
    /* Overload operators */                                            \
    Vec##N& operator=(const T* pval) {                                  \
        Set(pval);                                                      \
        return *this;                                                   \
    }                                                                   \
    Vec##N& operator=(const T val) {                                    \
        Set(val);                                                       \
        return *this;                                                   \
    }                                                                   \
    Vec##N& operator=(const Vec##N& v) {                                \
        Set(v);                                                         \
        return *this;                                                   \
    }                                                                   \
                                                                        \
    T& operator[](size_t index) {                                       \
        assert(index < N);                                              \
        return data[index];                                             \
    }                                                                   \
    const T& operator[](size_t index) const {                           \
        assert(index < N);                                              \
        return data[index];                                             \
    }                                                                   \
    Vec##N& operator-() {                                               \
        (*this) = Negate(*this);                                        \
        return *this;                                                   \
    }                                                                   \
                                                                        \
    Vec##N& operator+=(const Vec##N& v) {                               \
        (*this) = (*this) + v;                                          \
        return *this;                                                   \
    }                                                                   \
    Vec##N& operator+=(const T val) {                                   \
        (*this) = (*this) + val;                                        \
        return *this;                                                   \
    }                                                                   \
    Vec##N& operator-=(const Vec##N& v) {                               \
        (*this) = (*this) - v;                                          \
        return *this;                                                   \
    }                                                                   \
    Vec##N& operator-=(const T val) {                                   \
        (*this) = (*this) - val;                                        \
        return *this;                                                   \
    }                                                                   \
    Vec##N& operator*=(const Vec##N& v) {                               \
        (*this) = (*this) * v;                                          \
        return *this;                                                   \
    }                                                                   \
    Vec##N& operator*=(const float val) {                               \
        (*this) = (*this) * val;                                        \
        return *this;                                                   \
    }                                                                   \
    Vec##N& operator/=(const float val) {                               \
        (*this) = (*this) / val;                                        \
        return *this;                                                   \
    }

template <typename T>
class Vec2 {
public:
    union {
        T data[2];
        struct {
            T x, y;
        };
        struct {
            T r, g;
        };
        struct {
            T u, v;
        };
    };
    /// Common functions
    __DECLARE_VEC_MEM_FUNC(2);
public:
    /// Constructors
    Vec2(const T x, const T y) { Set(x, y); }
    /// Setters
    void Set(const T x, const T y) {
        this->x = x;
        this->y = y;
    }

}; ///< class Vec2

template <typename T>
class Vec3 {
public:
    union {
        T data[3];
        struct {
            T x, y, z;
        };
        struct {
            T r, g, b;
        };
    };
    /// Common functions
    __DECLARE_VEC_MEM_FUNC(3);
public:
    /// Constructors
    Vec3(const T x, const T y, const T z) { Set(x, y, z); }
    /// Setters
    void Set(const T x, const T y, const T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

}; ///< class Vec3

template <typename T>
class Vec4 {
public:
    union {
        T data[4];
        struct {
            T x, y, z, w;
        };
        struct {
            T r, g, b, a;
        };
    };
    /// Common functions
    __DECLARE_VEC_MEM_FUNC(4);
public:
    /// Constructors
    Vec4(const T x, const T y, const T z, const T w) { Set(x, y, z, w); }
    /// Setters
    void Set(const T x, const T y, const T z, const T w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

}; ///< class Vec4


/// Macro for vector typedef
#define __DECLARE_VEC_TYPEDEF(N)       \
    using Vec##Nf = Vec##N<float>;     \
    using Vec##Nd = Vec##N<double>;    \
    using Vec##Ni8 = Vec##N<int8_t>;   \
    using Vec##Ni16 = Vec##N<int16_t>; \
    using Vec##Ni32 = Vec##N<int32_t>; \
    using Vec##Ni64 = Vec##N<int64_t>

/// Rename
__DECLARE_VEC_TYPEDEF(2);
__DECLARE_VEC_TYPEDEF(3);
__DECLARE_VEC_TYPEDEF(4);

/// Macro for common operations
#define __DECLARE_VEC_OP(N)                                           \
    template <typename T>                                             \
    Vec##N<T> AddByElement(const Vec##N<T>& a, const Vec##N<T>& b) {  \
        Vec##N<T> res;                                                \
        for (size_t i = 0; i < N; ++i) {                              \
            res[i] = a[i] + b[i];                                     \
        }                                                             \
        return res;                                                   \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> SubByElement(const Vec##N<T>& a, const Vec##N<T>& b) {  \
        Vec##N<T> res;                                                \
        for (size_t i = 0; i < N; ++i) {                              \
            res[i] = a[i] - b[i];                                     \
        }                                                             \
        return res;                                                   \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> MulByElement(const Vec##N<T>& a, const Vec##N<T>& b) {  \
        Vec##N<T> res;                                                \
        for (size_t i = 0; i < N; ++i) {                              \
            res[i] = a[i] * b[i];                                     \
        }                                                             \
        return res;                                                   \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> DivByElement(const Vec##N<T>& a, const Vec##N<T>& b) {  \
        Vec##N<T> res;                                                \
        for (size_t i = 0; i < N; ++i) {                              \
            res[i] = a[i] / b[i];                                     \
        }                                                             \
        return res;                                                   \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    Vec##N<T> Dot(const Vec##N<T>& a, const Vec##N<T>& b) {           \
        return (a * b).Sum();                                         \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    Vec##N<T> Negate(const Vec##N<T>& v) {                            \
        Vec##N<T> res;                                                \
        for (size_t i = 0; i < N; ++i) {                              \
            res[i] = -v[i];                                           \
        }                                                             \
        return res;                                                   \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    Vec##N<T> Abs(const Vec##N<T>& v) {                               \
        Vec##N<T> res;                                                \
        for (size_t i = 0; i < N; ++i) {                              \
            res[i] = v[i] < 0 ? -v[i] : v[i];                         \
        }                                                             \
        return res;                                                   \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    Vec##N<T> Sqrt(const Vec##N<T>& v) {                              \
        Vec##N<T> res;                                                \
        for (size_t i = 0; i < N; ++i) {                              \
            res[i] = std::sqrt(v[i]);                                 \
        }                                                             \
        return res;                                                   \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    Vec##N<T> Pow(const Vec##N<T>& v, const float exponent) {         \
        Vec##N<T> res;                                                \
        for (size_t i = 0; i < N; ++i) {                              \
            res[i] = std::pow(v[i], exponent);                        \
        }                                                             \
        return res;                                                   \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    T Length(const Vec##N<T>& v) {                                    \
        return std::sqrt(Dot(v, v));                                  \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    void Normalize(Vec##N<T>& v) {                                    \
        v /= v.Length();                                              \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    std::ostream& operator<<(std::ostream& out, const Vec##N<T>& v) { \
        out.precision(4);                                             \
        out.setf(std::ios::fixed);                                    \
        bool first = true;                                            \
        for (const auto& val : v.data) {                              \
            out << (first ? "(" : ", ") << val;                       \
            first = false;                                            \
        }                                                             \
        return out << ")";                                            \
    }                                                                 \
                                                                      \
    template <typename T>                                             \
    Vec##N<T> operator+(const Vec##N<T>& a, const Vec##N<T>& b) {     \
        return AddByElement(a, b);                                    \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator+(const Vec##N<T>& v, const T val) {            \
        return v + Vec##N<T>(val);                                    \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator+(const T val, const Vec##N<T>& v) {            \
        return v + val;                                               \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator-(const Vec##N<T>& a, const Vec##N<T>& b) {     \
        return SubByElement(a, b);                                    \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator-(const Vec##N<T>& v, const T val) {            \
        return v - Vec##N<T>(val);                                    \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator-(const T val, const Vec##N<T>& v) {            \
        return Vec##N<T>(val) - v;                                    \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator*(const Vec##N<T>& a, const Vec##N<T>& b) {     \
        return MulByElement(a, b);                                    \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator*(const Vec##N<T>& v, const T val) {            \
        return v * Vec##N<T>(val);                                    \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator*(const T val, const Vec##N<T>& v) {            \
        return v * val;                                               \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator/(const Vec##N<T>& v, const T val) {            \
        return DivByElement(v, Vec##N<T>(val));                       \
    }                                                                 \
    template <typename T>                                             \
    Vec##N<T> operator/(const T val, const Vec##N<T>& v) {            \
        return DivByElement(Vec##N<T>(val), v);                       \
    }

/// Declaration of common operations
__DECLARE_VEC_OP(2);
__DECLARE_VEC_OP(3);
__DECLARE_VEC_OP(4);

template <typename T>
Vec3<T> Cross3(const Vec3<T>& a, const Vec3<T>& b) {
    return {
        a.y * b.z - a.z * b.y, 
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

/// Accelerate for float
#ifdef USE_ISPC

/// Macro for common operations using ispc
#define __DECLARE_VEC_OP_FLOAT(N)                                     \
    template <>                                                       \
    Vec##N<float> AddByElement(const Vec##N<float>& a,                \
                               const Vec##N<float>& b) {              \
        Vec##N<float> res;                                            \
        ispc::AddByElement(res.data, a.data, b.data, N);              \
        return res;                                                   \
    }                                                                 \
    template <>                                                       \
    Vec##N<float> SubByElement(const Vec##N<float>& a,                \
                               const Vec##N<float>& b) {              \
        Vec##N<float> res;                                            \
        ispc::SubByElement(res.data, a.data, b.data, N);              \
        return res;                                                   \
    }                                                                 \
    template <>                                                       \
    Vec##N<float> MulByElement(const Vec##N<float>& a,                \
                               const Vec##N<float>& b) {              \
        Vec##N<float> res;                                            \
        ispc::MulByElement(res.data, a.data, b.data, N);              \
        return res;                                                   \
    }                                                                 \
    template <>                                                       \
    Vec##N<float> DivByElement(const Vec##N<float>& a,                \
                               const Vec##N<float>& b) {              \
        Vec##N<float> res;                                            \
        ispc::DivByElement(res.data, a.data, b.data, N);              \
        return res;                                                   \
    }                                                                 \
                                                                      \
    template <>                                                       \
    Vec##N<float> Negate(const Vec##N<float>& v) {                    \
        Vec##N<float> res;                                            \
        ispc::Negate(res.data, v.data, N);                            \
        return res;                                                   \
    }                                                                 \
                                                                      \
    template <>                                                       \
    Vec##N<float> Abs(const Vec##N<float>& v) {                       \
        Vec##N<float> res;                                            \
        ispc::Absolute(res.data, v.data, N);                          \
        return res;                                                   \
    }                                                                 \
                                                                      \
    template <>                                                       \
    Vec##N<float> Sqrt(const Vec##N<float>& v) {                      \
        Vec##N<float> res;                                            \
        ispc::Sqrt(res.data, v.data, N);                              \
        return res;                                                   \
    }                                                                 \
                                                                      \
    template <>                                                       \
    Vec##N<float> Pow(const Vec##N<float>& v, const float exponent) { \
        Vec##N<float> res;                                            \
        ispc::Power(res.data, v.data, N, exponent);                   \
        return res;                                                   \
    }

/// Declaration of common operations for float
__DECLARE_VEC_OP_FLOAT(2);
__DECLARE_VEC_OP_FLOAT(3);
__DECLARE_VEC_OP_FLOAT(4);

template <typename T>
Vec3<float> Cross3(const Vec3<float>& a, const Vec3<float>& b) {
    Vec3<float> res;
    ispc::Cross3(res.data, a.data, b.data);
    return res;
}

#endif

}; ///< namespace Lumi
