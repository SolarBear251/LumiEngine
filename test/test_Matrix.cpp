/**
 * @file       test_Matrix.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-03-28
 *
 * @brief    Test cases for Matrix
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

#include <gtest/gtest.h>

#include <lumi/math/Mat.h>
#include <lumi/utils.h>

using namespace lumi;

TEST(basic, Mat3x3f) {
    Mat3x3f m;
    LogInfo(m);
    ASSERT_EQ(sizeof(m), sizeof(float) * 3 * 3);
}