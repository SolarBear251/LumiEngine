/**
 * @file       Vec.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-05
 * 
 * @brief    Data structure for N-dimension vectors.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#pragma once

#include <lumi/math/functions.h>
#include <lumi/math/ispc.h>
#include <lumi/utils.h>

#include <initializer_list>
#include <iostream>
#include <cstring>
#include <cstdint>

namespace lumi {

/// ==================== Macros ========================

/// Member functions
#define __DECLARE_VEC_MEM_FUNC(N)                                       \
   public:                                                              \
    /* Constructors */                                                  \
    Vec() { Set(T()); }                                                 \
    explicit Vec(const T& val) { Set(val); }                            \
    Vec(const Vec& v) { Set(v); }                                       \
    Vec(const std::initializer_list<const T>& list) { Set(list); }      \
                                                                        \
    /* Setters */                                                       \
    void Set(const T& val) {                                            \
        for (auto& v : data) v = val;                                   \
    }                                                                   \
    void Set(const T* pval) { std::memcpy(data, pval, sizeof(T) * N); } \
    void Set(const Vec& v) {                                            \
        if (this == &v) return;                                         \
        std::memcpy(this, &v, sizeof(v));                               \
    }                                                                   \
    void Set(const std::initializer_list<const T>& list) {              \
        Assert(list.size() <= N);                                       \
        size_t i = 0;                                                   \
        for (auto& val : list) {                                        \
            data[i++] = val;                                            \
        }                                                               \
        while (i < N) {                                                 \
            data[i++] = 0;                                              \
        }                                                               \
    }                                                                   \
                                                                        \
    /* Assign operators */                                              \
    Vec& operator=(const T* pval) {                                     \
        Set(pval);                                                      \
        return *this;                                                   \
    }                                                                   \
    Vec& operator=(const T& val) {                                      \
        Set(val);                                                       \
        return *this;                                                   \
    }                                                                   \
    Vec& operator=(const Vec& v) {                                      \
        Set(v);                                                         \
        return *this;                                                   \
    }                                                                   \
                                                                        \
    /* Getters */                                                       \
    T& operator[](size_t index) {                                       \
        Assert(index < N);                                              \
        return data[index];                                             \
    }                                                                   \
    const T& operator[](size_t index) const {                           \
        Assert(index < N);                                              \
        return data[index];                                             \
    }                                                                   \
                                                                        \
    /**                                                                 \
     * @brief    Get the sum of each value in the vector.               \
     *                                                                  \
     * @return   T   Sum of each value.                                 \
     */                                                                 \
    T Sum() const { return lumi::Sum(data, N); }                        \
                                                                        \
    /**                                                                 \
     * @brief    Get the length of the vector.                          \
     *                                                                  \
     * @return   float   Length of the vector.                          \
     */                                                                 \
    float Length() const { return Sqrt(SquareSum(data, N)); }           \
                                                                        \
    /**                                                                 \
     * @brief    Check whether it is a zero vector.                     \
     *                                                                  \
     * @return   true       Is a zero vector.                           \
     * @return   false      Not a zero vector.                          \
     */                                                                 \
    bool IsZeroVec() const { return IsZero(SquareSum(data, N)); }       \
                                                                        \
    /**                                                                 \
     * @brief    Negate each value in the vector.                       \
     *                                                                  \
     * @return   Vec&    Reference of this vector                       \
     */                                                                 \
    Vec& Negate() {                                                     \
        lumi::Negate(data, N);                                          \
        return *this;                                                   \
    }                                                                   \
                                                                        \
    /**                                                                 \
     * @brief    Absolute each value in the vector.                     \
     *                                                                  \
     * @return   Vec&    Reference of this vector                       \
     */                                                                 \
    Vec& Abs() {                                                        \
        lumi::Abs(data, N);                                             \
        return *this;                                                   \
    }                                                                   \
                                                                        \
    /**                                                                 \
     * @brief    Normalize this vector.                                 \
     *           Valid only if data type is float or double             \
     *                                                                  \
     * @return   Vec&    Reference of this vector                       \
     */                                                                 \
    Vec& Normalize() {                                                  \
        Assert(std::is_floating_point<T>::value,                        \
               "Normalize a non-floating-point vector!");               \
        float len = Length();                                           \
        Assert(!IsZero(len), "Divided by zero!");                       \
        MulNumber(data, 1.0f / len, N);                                 \
        return *this;                                                   \
    }

/// ==================== Declarations ========================

/// Template for N-dimension vector
template <typename T, size_t N>
struct Vec {
    T data[N];

    /// Common functions
    __DECLARE_VEC_MEM_FUNC(N);

};  ///< struct Vec<T, N>


/// Template for 2-dimension vector
template <typename T>
struct Vec<T, 2> {
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

    /// Constructors
    Vec(const T& x, const T& y) { Set(x, y); }
    /// Setters
    void Set(const T& x, const T& y) {
        this->x = x;
        this->y = y;
    }

};  ///< struct Vec<T, 2>

/// Template for 3-dimension vector
template <typename T>
struct Vec<T, 3> {
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

    /// Constructors
    Vec(const T& x, const T& y, const T& z) { Set(x, y, z); }
    /// Setters
    void Set(const T& x, const T& y, const T& z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

};  ///< struct Vec<T, 3>

/// Template for 4-dimension vector
template <typename T>
struct Vec<T, 4> {
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

    /// Constructors
    Vec(const T& x, const T& y, const T& z, const T& w) { Set(x, y, z, w); }
    /// Setters
    void Set(const T& x, const T& y, const T& z, const T& w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

};  ///< struct Vec<T, 4>

/// Rename
using Vec2f   = Vec<float,   2>;
using Vec2d   = Vec<double,  2>;
using Vec2i   = Vec<int32_t, 2>;
using Vec2i32 = Vec<int32_t, 2>;
using Vec2u8  = Vec<uint8_t, 2>;

using Vec3f   = Vec<float,   3>;
using Vec3d   = Vec<double,  3>;
using Vec3i   = Vec<int32_t, 3>;
using Vec3i32 = Vec<int32_t, 3>;
using Vec3u8  = Vec<uint8_t, 3>;

using Vec4f   = Vec<float,   4>;
using Vec4d   = Vec<double,  4>;
using Vec4i   = Vec<int32_t, 4>;
using Vec4i32 = Vec<int32_t, 4>;
using Vec4u8  = Vec<uint8_t, 4>;


/// ==================== Operations ========================

/// Overload output operator
template <typename T, size_t N>
inline std::ostream& operator<<(std::ostream& out, const Vec<T, N>& v) {
    std::streamsize prec = out.precision();
    out.precision(4);
    out.setf(std::ios::fixed);

    out << "Vec" << N;
    bool first = true;
    for (const auto& val : v.data) {
        /* Use unary '+' operator to print a char as a number */
        out << (first ? "(" : ", ") << +val;
        first = false;
    }
    out << ")";

    out.unsetf(std::ios::fixed);
    out.precision(prec);
    return out;
}

/// Binary operations
template <typename T, size_t N>
inline Vec<T, N> Add(const Vec<T, N>& a, const Vec<T, N>& b) {
    Vec<T, N> res;
    AddByElement(res.data, a.data, b.data, N);
    return res;
}

template <typename T, size_t N>
inline Vec<T, N> Sub(const Vec<T, N>& a, const Vec<T, N>& b) {
    Vec<T, N> res;
    SubByElement(res.data, a.data, b.data, N);
    return res;
}

template <typename T, size_t N>
inline Vec<T, N> Mul(const Vec<T, N>& a, const Vec<T, N>& b) {
    Vec<T, N> res;
    MulByElement(res.data, a.data, b.data, N);
    return res;
}

template <typename T, size_t N>
inline Vec<T, N> MulNumber(const Vec<T, N>& a, const float& num) {
    /// Only allow floating point numbers!
    Vec<T, N> res(a);
    lumi::MulNumber(res.data, num, N);
    return res;
}

template <typename T, size_t N>
inline Vec<T, N> DivNumber(const Vec<T, N>& a, const float& num) {
    /// Only allow floating point numbers!
    Assert(num != 0, "Divided by zero!");
    Vec<T, N> res(a);
    lumi::MulNumber(res.data, 1.0f / num, N);
    return res;
}

template <typename T, size_t N>
inline T Dot(const Vec<T, N>& a, const Vec<T, N>& b) {
    return Mul(a, b).Sum();
}

template <typename T>
inline Vec<T, 3> Cross3(const Vec<T, 3>& a, const Vec<T, 3>& b) {
    Vec<T, 3> res;
    lumi::Cross3(res.data, a.data, b.data);
    return res;
}

/// Operators overload
template <typename T, size_t N>
inline Vec<T, N> operator+(const Vec<T, N>& a, const Vec<T, N>& b) {
    return Add(a, b);
}

template <typename T, size_t N>
inline Vec<T, N> operator+(const Vec<T, N>& v, const T& val) {
    return v + Vec<T, N>(val);
}

template <typename T, size_t N>
inline Vec<T, N> operator+(const T& val, const Vec<T, N>& v) {
    return v + val;
}

template <typename T, size_t N>
inline Vec<T, N> operator-(const Vec<T, N>& a, const Vec<T, N>& b) {
    return Sub(a, b);
}

template <typename T, size_t N>
inline Vec<T, N> operator-(const Vec<T, N>& v, const T& val) {
    return v - Vec<T, N>(val);
}

template <typename T, size_t N>
inline Vec<T, N> operator-(const T& val, const Vec<T, N>& v) {
    return Vec<T, N>(val) - v;
}

template <typename T, size_t N>
inline Vec<T, N> operator*(const Vec<T, N>& a, const Vec<T, N>& b) {
    return Mul(a, b);
}

template <typename T, size_t N>
inline Vec<T, N> operator*(const Vec<T, N>& v, const float& val) {
    return MulNumber(v, val);
}

template <typename T, size_t N>
inline Vec<T, N> operator*(const float& val, const Vec<T, N>& v) {
    return v * val;
}

template <typename T, size_t N>
inline Vec<T, N> operator/(const Vec<T, N>& v, const float& val) {
    return DivNumber(v, val);
}

template <typename T, size_t N>
inline Vec<T, N>& operator+=(Vec<T, N>& a, const Vec<T, N>& b) {
    a = a + b;
    return a;
}

template <typename T, size_t N>
inline Vec<T, N>& operator+=(Vec<T, N>& a, const T& val) {
    a = a + val;
    return a;
}

template <typename T, size_t N>
inline Vec<T, N>& operator-=(Vec<T, N>& a, const Vec<T, N>& b) {
    a = a - b;
    return a;
}

template <typename T, size_t N>
inline Vec<T, N>& operator-=(Vec<T, N>& a, const T& val) {
    a = a - val;
    return a;
}

template <typename T, size_t N>
inline Vec<T, N>& operator*=(Vec<T, N>& a, const Vec<T, N>& b) {
    a = a * b;
    return a;
}

template <typename T, size_t N>
inline Vec<T, N>& operator*=(Vec<T, N>& a, const float& val) {
    a = a * val;
    return a;
}

template <typename T, size_t N>
inline Vec<T, N>& operator/=(Vec<T, N>& a, const float& val) {
    a = a / val;
    return a;
}

template <typename T, size_t N>
inline bool operator==(const Vec<T, N>& a, const Vec<T, N>& b) {
    return (a - b).IsZeroVec();
}

}; ///< namespace lumi
