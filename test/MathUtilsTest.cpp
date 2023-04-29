#include <gtest/gtest.h>
#include "MathUtils.h"

TEST(MathUtilsTest, Modulo) {
	ASSERT_EQ(3, modulo(3, 4)) << "3 % 4 = 3";
	ASSERT_EQ(0, modulo(4, 4)) << "4 % 4 = 0";
	ASSERT_EQ(3, modulo(-1, 4)) << "-1 % 4 = 3";
	ASSERT_EQ(1, modulo(-3, 4)) << "-3 % 4 = 1";
	ASSERT_EQ(1, modulo(1, 4)) << "1 % 4 = 1";
}

TEST(MathUtilsTest, Sign) {
	ASSERT_EQ(1, sign(3)) << "sign(3) = 1";
	ASSERT_EQ(0, sign(0)) << "sign(0) = 0";
	ASSERT_EQ(-1, sign(-3)) << "sign(-3) = -1";
}