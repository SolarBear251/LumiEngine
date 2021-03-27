/**
 * @file       test_Vector.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-02-06
 *
 * @brief    Test cases for Vectors
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

#include <gtest/gtest.h>
#include <lumi/math/Vec.h>
#include <lumi/utils.h>

#include <iostream>

using namespace lumi;

TEST(basic, Vec2i) {
    Vec2i v2;
    LogInfo(v2);
    ASSERT_TRUE(v2.IsZeroVec());
    ASSERT_EQ(v2.Length(), 0);
    ASSERT_EQ(sizeof(v2), sizeof(int) * 2);
    v2 = {-1, -2};
    LogInfo(v2.x, ",", v2.y);
    LogInfo(v2.r, ",", v2.g);
    LogInfo(v2.u, ",", v2.v);

    Vec2i v(v2);
    LogInfo(v);
    LogInfo(v[0], ",", v[1]);

    ASSERT_EQ(-3, v.Sum());
    LogInfo(Sqrt(1 + 4));
    ASSERT_TRUE(IsZero(v.Length() - Sqrt(1 + 4)));

    LogInfo(v.Negate());
    LogInfo(v.Negate());
    LogInfo(v.Abs());
    // LogInfo(v.Normalize());
    LogInfo(v.Length());
}

TEST(basic, Vec3f) {
    Vec3f v3(1);
    std::cout << v3 << std::endl;
    ASSERT_FALSE(v3.IsZeroVec());
    ASSERT_EQ(sizeof(v3), sizeof(float) * 3);
    v3 = {1, 2, 3};
    LogInfo(v3.x, ", ", v3.y, ", ", v3.z);
    LogInfo(v3.r, ", ", v3.g, ", ", v3.b);

    Vec3f v(v3);
    LogInfo(v);
    LogInfo(v[0], ", ", v[1], v[2]);

    LogInfo("sum: ", v.Sum());
    ASSERT_EQ(6, v.Sum());
    LogInfo(Sqrt(1 + 4 + 9));
    ASSERT_TRUE(IsZero(v.Length() - Sqrt(1 + 4 + 9)));

    LogInfo(v.Negate());
    LogInfo(v.Abs());
    LogInfo(v.Normalize());
    LogInfo(v.Length());
}

TEST(basic, Vec4d) {
    Vec4d v4;
    LogInfo(v4);
    ASSERT_TRUE(v4.IsZeroVec());
    ASSERT_EQ(sizeof(v4), sizeof(double) * 4);
    v4 = {1, 2, 3, 4};
    LogInfo(v4.x, ", ", v4.y, ", ", v4.z, ", ", v4.w);
    LogInfo(v4.r, ", ", v4.g, ", ", v4.b, ", ", v4.a);

    Vec4d v(v4);
    LogInfo(v);
    LogInfo(v[0], ", ", v[1], v[2], ", ", v[3]);

    ASSERT_EQ(10, v.Sum());
    LogInfo(Sqrt(1 + 4 + 9 + 16));
    ASSERT_TRUE(IsZero(v.Length() - Sqrt(1 + 4 + 9 + 16)));

    LogInfo(v.Negate());
    LogInfo(v.Negate());
    LogInfo(v.Abs());
    LogInfo(v.Normalize());
    LogInfo(v.Length());
}