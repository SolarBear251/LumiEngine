/**
 * @file       Mat.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-03-28
 *
 * @brief    Data structure for ROWS x COLS matrix.
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

#pragma once

#include <lumi/math/Vec.h>

namespace lumi {

template <typename T, size_t ROWS, size_t COLS>
struct Mat {
    Vec<T, COLS> data[ROWS];

    Mat() { Set(T()); }
    explicit Mat(const T& val) { Set(val); }
    Mat(const Mat& v) { Set(v); }
    Mat(const std::initializer_list<const T>& list) {
        Set(list);
    }

    /// Setters
    void Set(const T& val) {
        for (auto& v : data) v.Set(val);
    }
    void Set(const T* pval) {
        constexpr int SIZE = ROWS * COLS;
        std::memcpy(data, pval, sizeof(T) * SIZE);
    }
    void Set(const Mat& m) {
        if (this == &m) return;
        std::memcpy(this, &m, sizeof(m));
    }
    void Set(const std::initializer_list<const T>& list) {
        constexpr int SIZE = ROWS * COLS;
        // Must be exactly ROWS x COLS!
        Assert(list.size() == SIZE); 
        size_t i = 0;
        T* head = reinterpret_cast<T*>(data);
        for (auto& val : list) {
            head[i++] = val;
        }
    }

    /// Assign operators
    Mat& operator=(const T* pval) {
        Set(pval);
        return *this;
    }
    Mat& operator=(const T& val) {
        Set(val);
        return *this;
    }
    Mat& operator=(const Mat& m) {
        Set(m);
        return *this;
    }

    /// Getters
    Vec<T, COLS>& operator[](size_t index) {
        Assert(index < ROWS);
        return data[index];
    }
    const Vec<T, COLS>& operator[](size_t index) const {
        Assert(index < ROWS);
        return data[index];
    }

};  ///< struct Mat

/// Rename
using Mat3x3f = Mat<float, 3, 3>;
using Mat4x4f = Mat<float, 4, 4>;

/// ==================== Operations ========================

/// Overload output operator
template <typename T, size_t ROWS, size_t COLS>
inline std::ostream& operator<<(std::ostream& out,
                                const Mat<T, ROWS, COLS>& m) {
    std::streamsize prec = out.precision();
    out.precision(4);
    out.setf(std::ios::fixed);

    out << std::endl << "Mat" << ROWS << 'x' << COLS << ':' << std::endl;
    for (const auto& v : m.data) {
        bool first = true;
        for (const auto& val : v.data) {
            if (!first) out << '\t';
            /* Use unary '+' operator to print a char as a number */
            out << +val;
            first = false;
        }
        out << std::endl;
    }

    out.unsetf(std::ios::fixed);
    out.precision(prec);
    return out;
}

}; ///< namespace lumi