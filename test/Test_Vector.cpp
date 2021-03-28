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

TEST(basic, Vec9f) {
    Vec<float, 9> v9;
    std::cout << v9 << std::endl;
    ASSERT_TRUE(v9.IsZeroVec());
    ASSERT_EQ(sizeof(v9), sizeof(float) * 9);
    v9 = {1, 2, -3, 4, -5, 6, 7, -8};
    LogInfo(v9);

    Vec<float, 9> v(v9);
    LogInfo(v);
    LogInfo(v[0], v[1], v[2], v[7], v[8]);

    LogInfo("sum: ", v.Sum());
    ASSERT_EQ(1 + 2 + -3 + 4 + -5 + 6 + 7 + -8, v.Sum());
    LogInfo(Sqrt(1 + 4 + 9 + 16 + 25 + 36 + 49 + 64));
    ASSERT_TRUE(IsZero(v.Length() - Sqrt(1 + 4 + 9 + 16 + 25 + 36 + 49 + 64)));

    LogInfo(v.Negate());
    LogInfo(v.Abs());
    LogInfo(v.Normalize());
    LogInfo(v.Length());
}

TEST(basic, Vec4u8) {
    Vec4u8 v4;
    LogInfo(v4);
    ASSERT_TRUE(v4.IsZeroVec());
    ASSERT_EQ(v4.Length(), 0);
    ASSERT_EQ(sizeof(v4), sizeof(uint8_t) * 4);
    v4 = {1, 2, 3, 4};
    LogInfo(+v4.x, +v4.y, +v4.z, +v4.w);
    LogInfo(+v4.r, +v4.g, +v4.b, +v4.a);

    Vec4u8 v(v4);
    LogInfo(v);
    LogInfo(+v[0], +v[1], +v[2], +v[3]);

    ASSERT_EQ(10, v.Sum());
    LogInfo(Sqrt(1 + 4 + 9 + 16));
    ASSERT_TRUE(IsZero(v.Length() - Sqrt(1 + 4 + 9 + 16)));

    LogInfo(v.Negate());
    LogInfo(v.Negate());
    LogInfo(v.Abs());
    // LogInfo(v.Normalize());
    LogInfo(v.Length());
}

TEST(op, Vec3f) {
    Vec3f a{1, 2, 3.3f};
    Vec3f b{1, 2, 3.3f};

    ASSERT_EQ(a, b); //==
    ASSERT_EQ(a + b, Vec3f({2, 4, 6.6f}));
    ASSERT_EQ(a - b, Vec3f({0, 0, 0}));
    ASSERT_EQ(a * b, Vec3f({1, 4, 3.3f * 3.3f}));
    ASSERT_EQ(a + 2.f, Vec3f({3, 4, 5.3f}));
    ASSERT_EQ(2.f + a, Vec3f({3, 4, 5.3f}));
    ASSERT_EQ(a - 2.f, Vec3f({-1, 0, 1.3f}));
    ASSERT_EQ(2.f - a, Vec3f({1, 0, -1.3f}));
    ASSERT_EQ(a * 2.f, Vec3f({2, 4, 6.6f}));
    ASSERT_EQ(2.f * a, Vec3f({2, 4, 6.6f}));
    ASSERT_EQ(a / 2.f, Vec3f({0.5f, 1, 3.3f / 2}));

    ASSERT_TRUE(IsZero(1 + 2 * 2 + 3.3 * 3.3 - Dot(a, b)));

    a += b;
    ASSERT_EQ(a, Vec3f({2, 4, 6.6f}));
    a -= {3, 3, 3};
    ASSERT_EQ(a, Vec3f({-1, 1, 3.6f}));
    a *= {1., 2, 3};
    ASSERT_EQ(a, Vec3f({-1, 2, 3.6f * 3}));
    a /= 2;
    ASSERT_EQ(a, Vec3f({-0.5, 1, 3.6f * 3 / 2}));

    Vec3f c = Cross3(a, b).Normalize();
    LogInfo(c, Dot(a, c), Dot(b, c));
    ASSERT_TRUE(IsZero(Dot(a, c)));
    ASSERT_TRUE(IsZero(Dot(c, b)));
}

TEST(op, Vec3i) {
    Vec3i a{5, 6, 7};
    Vec3i b{5, 6, 7};

    ASSERT_EQ(a, b);  //==
    ASSERT_EQ(a + b, Vec3i({10, 12, 14}));
    ASSERT_EQ(a - b, Vec3i({0, 0, 0}));
    ASSERT_EQ(a * b, Vec3i({25, 36, 49}));
    ASSERT_EQ(a + 2, Vec3i({7, 8, 9}));
    ASSERT_EQ(2 + a, Vec3i({7, 8, 9}));
    ASSERT_EQ(a - 2, Vec3i({3, 4, 5}));
    ASSERT_EQ(2 - a, Vec3i({-3, -4, -5}));
    ASSERT_EQ(a * 2, Vec3i({10, 12, 14}));
    ASSERT_EQ(2 * a, Vec3i({10, 12, 14}));
    ASSERT_EQ(a / 2, Vec3i({2, 3, 3}));

    ASSERT_TRUE(IsZero(25 + 36 + 49 - Dot(a, b)));

    a += b;
    ASSERT_EQ(a, Vec3i({10, 12, 14}));
    a -= {3, 3, 3};
    ASSERT_EQ(a, Vec3i({7, 9, 11}));
    a *= {1, 2, 3};
    ASSERT_EQ(a, Vec3i({7, 18, 33}));
    a /= 2;
    ASSERT_EQ(a, Vec3i({3, 9, 16}));

    Vec3i c = Cross3(a, b);
    LogInfo(c, Dot(a, c), Dot(b, c));
    ASSERT_TRUE(IsZero(Dot(a, c)));
    ASSERT_TRUE(IsZero(Dot(c, b)));
}

TEST(op, Vec4u8) {
    Vec4u8 a{5, 6, 7};
    Vec4u8 b{5, 6, 7};

    LogInfo(a);
    ASSERT_EQ(a, b);  //==
    ASSERT_EQ(a + b, Vec4u8({10, 12, 14, 0}));
    ASSERT_EQ(a - b, Vec4u8({0, 0, 0, 0}));
    ASSERT_EQ(a * b, Vec4u8({25, 36, 49, 0}));
    ASSERT_EQ(a + uint8_t(2), Vec4u8({7, 8, 9, 2}));
    ASSERT_EQ(uint8_t(2) + a, Vec4u8({7, 8, 9, 2}));
    ASSERT_EQ(a - uint8_t(2), Vec4u8({3, 4, 5, uint8_t(-2)}));
    ASSERT_EQ(uint8_t(2) - a,
              Vec4u8({uint8_t(-3), uint8_t(-4), uint8_t(-5), 2}));
    ASSERT_EQ(a * 2, Vec4u8({10, 12, 14, 0}));
    ASSERT_EQ(2 * a, Vec4u8({10, 12, 14, 0}));
    ASSERT_EQ(a / 2, Vec4u8({2, 3, 3, 0}));

    ASSERT_TRUE(IsZero(25 + 36 + 49 - Dot(a, b)));

    a += {5, 6, 7, 8};
    ASSERT_EQ(a, Vec4u8({10, 12, 14, 8}));
    a -= {3, 3, 3, 2};
    ASSERT_EQ(a, Vec4u8({7, 9, 11, 6}));
    a *= {1, 2, 3, 4};
    ASSERT_EQ(a, Vec4u8({7, 18, 33, 24}));
    a /= 2;
    ASSERT_EQ(a, Vec4u8({3, 9, 16, 12}));

    // a /= 0;
}