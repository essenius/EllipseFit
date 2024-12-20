// Copyright 2023-2024 Rik Essenius
// 
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
// except in compliance with the License. You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.

#include <gtest/gtest.h>

#include "TestHelper.h"
#include "Angle.h"

using namespace EllipseMath;

namespace EllipseFitTest {

	TEST(AngleTest, QuadrantTest) {
		constexpr double AngleEpsilon = 0.001;
		auto angle = Angle{ AngleEpsilon };
	    EXPECT_EQ(1, angle.getQuadrant());
		angle.value = M_PI / 2 - AngleEpsilon;
		EXPECT_EQ(1, angle.getQuadrant());

		angle.value = M_PI - AngleEpsilon;
		EXPECT_EQ(2, angle.getQuadrant());
		angle.value = M_PI / 2 + AngleEpsilon;
		EXPECT_EQ(2, angle.getQuadrant());

		angle.value = -M_PI + AngleEpsilon;
		EXPECT_EQ(3, angle.getQuadrant());
		angle.value = -M_PI / 2 - AngleEpsilon;
		EXPECT_EQ(3, angle.getQuadrant());

		angle.value = -AngleEpsilon;
		EXPECT_EQ(4, angle.getQuadrant());
		angle.value = -M_PI / 2 + AngleEpsilon;
		EXPECT_EQ(4, angle.getQuadrant());
	}

	TEST(AngleTest, CompareTest) {
		constexpr Angle A {M_PI};
		constexpr Angle B {M_PI};
		expectAnglesEqual(A, { M_PI }, "a = M_PI");
		expectAnglesEqual(A, B, "a=b");
		expectAnglesEqual({ M_PI }, { M_PI }, "M_PI = M_PI");
	}

	TEST(AngleTest, OperatorTest) {
		constexpr Angle A {M_PI};
		const auto b = A - 7 * M_PI / 3;
		expectDoubleEqual(2 * M_PI / 3, b, "operator- on double");
		const auto c = A - Angle{ M_PI / 3 };
		expectAnglesEqual({ 2 * M_PI / 3 }, c, "operator- on angle");
	}

	TEST(AngleTest, Times10Test) {
		constexpr Angle A{ -M_PI };
		EXPECT_EQ(-1800, A.degreesTimes10()) << "Angle to degrees times 10 is correct";
	}

	TEST(AngleTest, Normalize) {
		expectDoubleEqual(M_PI, Angle::normalized(M_PI), "Angle normalize PI is correct");
		expectDoubleEqual(-M_PI, Angle::normalized(-M_PI), "Angle normalize -PI is correct");
		expectDoubleEqual(0.1 * M_PI, Angle::normalized(-3.9 * M_PI), "Angle normalize -3.9 * PI is correct");
		expectDoubleEqual(-0.9 * M_PI, Angle::normalized(13.1 * M_PI), "Angle normalize 13.1 * PI is correct");

	}
}