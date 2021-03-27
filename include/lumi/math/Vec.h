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

#include <lumi/math/functions.h>
#include <lumi/math/ispc.h>
#include <lumi/utils.h>

#include <initializer_list>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <type_traits>

namespace lumi {

/// ==================== Macros ========================

/// Macro for member functions
#define __DECLARE_VEC_MEM_FUNC(N)                                       \
   public:                                                              \
    /* Constructors */                                                  \
    Vec##N() { Set(T()); }                                              \
    explicit Vec##N(const T val) { Set(val); }                          \
    Vec##N(const Vec##N& v) { Set(v); }                                 \
    Vec##N(std::initializer_list<const T> list) { Set(list); }          \
                                                                        \
    /* Setters */                                                       \
    void Set(const T val) {                                             \
        for (auto& v : data) v = val;                                   \
    }                                                                   \
    void Set(const T* pval) { std::memcpy(data, pval, sizeof(T) * N); } \
    void Set(const Vec##N& v) {                                         \
        if (this == &v) return;                                         \
        std::memcpy(this, &v, sizeof(v));                               \
    }                                                                   \
    void Set(std::initializer_list<const T> list) {                     \
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
    bool IsZeroVec() const { return IsZero(Length()); }                 \
                                                                        \
    /**                                                                 \
     * @brief    Negate each value in the vector.                       \
     *                                                                  \
     * @return   Vec##N<T>&    Reference of this vector                 \
     */                                                                 \
    Vec##N<T>& Negate() {                                               \
        lumi::Negate(data, N);                                          \
        return *this;                                                   \
    }                                                                   \
                                                                        \
    /**                                                                 \
     * @brief    Absolute each value in the vector.                     \
     *                                                                  \
     * @return   Vec##N<T>&    Reference of this vector                 \
     */                                                                 \
    Vec##N<T>& Abs() {                                                  \
        lumi::Abs(data, N);                                             \
        return *this;                                                   \
    }                                                                   \
                                                                        \
    /**                                                                 \
     * @brief    Normalize this vector.                                 \
     *           Valid only if data type is float or double             \
     *                                                                  \
     *                                                                  \
     * @return   Vec##N<T>&    Reference of this vector                 \
     */                                                                 \
    Vec##N<T>& Normalize() {                                            \
        if (!std::is_floating_point<T>::value) {                        \
            Assert(false, "Normalize a non-floating-point vector!");    \
            return *this;                                               \
        }                                                               \
        float len = Length();                                           \
        if (IsZero(len)) {                                              \
            Assert(false, "Divided by zero!");                          \
            return *this;                                               \
        }                                                               \
        MulNumber(data, 1.0f / len, N);                                 \
        return *this;                                                   \
    }

/// Macro for binary operations
// #define __DECLARE_VEC_OP(N)                                           \
//     template <typename T>                                             \
//     Vec##N<T> AddByElement(const Vec##N<T>& a, const Vec##N<T>& b) {  \
//         Vec##N<T> res;                                                \
//         AddByElement(res.data, a.data, b.data, N);                    \
//         return res;                                                   \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> SubByElement(const Vec##N<T>& a, const Vec##N<T>& b) {  \
//         Vec##N<T> res;                                                \
//         SubByElement(res.data, a.data, b.data, N);                    \
//         return res;                                                   \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> MulByElement(const Vec##N<T>& a, const Vec##N<T>& b) {  \
//         Vec##N<T> res;                                                \
//         for (size_t i = 0; i < N; ++i) {                              \
//             res[i] = a[i] * b[i];                                     \
//         }                                                             \
//         return res;                                                   \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> DivByElement(const Vec##N<T>& a, const Vec##N<T>& b) {  \
//         Vec##N<T> res;                                                \
//         for (size_t i = 0; i < N; ++i) {                              \
//             res[i] = a[i] / b[i];                                     \
//         }                                                             \
//         return res;                                                   \
//     }                                                                 \
//                                                                       \
//     template <typename T>                                             \
//     Vec##N<T> operator+(const Vec##N<T>& a, const Vec##N<T>& b) {     \
//         return AddByElement(a, b);                                    \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator+(const Vec##N<T>& v, const T val) {            \
//         return v + Vec##N<T>(val);                                    \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator+(const T val, const Vec##N<T>& v) {            \
//         return v + val;                                               \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator-(const Vec##N<T>& a, const Vec##N<T>& b) {     \
//         return SubByElement(a, b);                                    \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator-(const Vec##N<T>& v, const T val) {            \
//         return v - Vec##N<T>(val);                                    \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator-(const T val, const Vec##N<T>& v) {            \
//         return Vec##N<T>(val) - v;                                    \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator*(const Vec##N<T>& a, const Vec##N<T>& b) {     \
//         return MulByElement(a, b);                                    \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator*(const Vec##N<T>& v, const T val) {            \
//         return v * Vec##N<T>(val);                                    \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator*(const T val, const Vec##N<T>& v) {            \
//         return v * val;                                               \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator/(const Vec##N<T>& v, const T val) {            \
//         return DivByElement(v, Vec##N<T>(val));                       \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> operator/(const T val, const Vec##N<T>& v) {            \
//         return DivByElement(Vec##N<T>(val), v);                       \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N& operator+=(const Vec##N& v) {                             \
//         (*this) = (*this) + v;                                        \
//         return *this;                                                 \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N& operator+=(const T val) {                                 \
//         (*this) = (*this) + val;                                      \
//         return *this;                                                 \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N& operator-=(const Vec##N& v) {                             \
//         (*this) = (*this) - v;                                        \
//         return *this;                                                 \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N& operator-=(const T val) {                                 \
//         (*this) = (*this) - val;                                      \
//         return *this;                                                 \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N& operator*=(const Vec##N& v) {                             \
//         (*this) = (*this) * v;                                        \
//         return *this;                                                 \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N& operator*=(const float val) {                             \
//         (*this) = (*this) * val;                                      \
//         return *this;                                                 \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N& operator/=(const float val) {                             \
//         (*this) = (*this) / val;                                      \
//         return *this;                                                 \
//     }                                                                 \
//     template <typename T>                                             \
//     Vec##N<T> Dot(const Vec##N<T>& a, const Vec##N<T>& b) {           \
//         return (a * b).Sum();                                         \
//     }                                                                 \

#define __DECLARE_VEC_OP(N)                                           \
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
    }

/// Macro for vector typedef
#define __DECLARE_VEC_TYPEDEF(N)         \
    using Vec##N##f = Vec##N<float>;     \
    using Vec##N##d = Vec##N<double>;    \
    using Vec##N##i8 = Vec##N<int8_t>;   \
    using Vec##N##i16 = Vec##N<int16_t>; \
    using Vec##N##i32 = Vec##N<int32_t>; \
    using Vec##N##i   = Vec##N<int32_t>; \
    using Vec##N##i64 = Vec##N<int64_t>

/// ==================== Declarations ========================

template <typename T>
struct Vec2 {
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
    Vec2(const T x, const T y) { Set(x, y); }
    /// Setters
    void Set(const T x, const T y) {
        this->x = x;
        this->y = y;
    }

}; ///< struct Vec2

template <typename T>
struct Vec3 {
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
    Vec3(const T x, const T y, const T z) { Set(x, y, z); }
    /// Setters
    void Set(const T x, const T y, const T z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

};  ///< struct Vec3

template <typename T>
struct Vec4 {
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
    Vec4(const T x, const T y, const T z, const T w) { Set(x, y, z, w); }
    /// Setters
    void Set(const T x, const T y, const T z, const T w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

};  ///< struct Vec4

/// Rename
__DECLARE_VEC_TYPEDEF(2);
__DECLARE_VEC_TYPEDEF(3);
__DECLARE_VEC_TYPEDEF(4);

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

template <typename T>
Vec3<float> Cross3(const Vec3<float>& a, const Vec3<float>& b) {
    Vec3<float> res;
    ispc::Cross3(res.data, a.data, b.data);
    return res;
}

}; ///< namespace lumi
