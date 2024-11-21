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

#include "MathUtils.h"
#include "Coordinate.h"

using namespace EllipseMath;

namespace EllipseFitTest {

	bool coordinateEqual(const Coordinate& a, const Coordinate& b) {
		return a == b;
	}

	TEST(CoordinateTest, AngleDistance) {
		constexpr Coordinate Base{ 4, 4 };
		EXPECT_DOUBLE_EQ(M_PI / 4, Base.getAngle().value) << "Angle OK";
		EXPECT_DOUBLE_EQ(sqrt(32), Base.getDistance()) << "Distance OK";
	}

	TEST(CoordinateTest, AngleFromDistanceFrom) {
		constexpr Coordinate Base{ 4, 4 };
		EXPECT_DOUBLE_EQ(5, Base.getDistanceFrom({ 0, 7 })) << "DistanceFrom OK";
		EXPECT_DOUBLE_EQ(-M_PI / 4, Base.getAngleFrom({ -4, 12 }).value) << "AngleFrom OK";
	}

	TEST(CoordinateTest, AngleOfZeroIsNotDefined) {
		EXPECT_TRUE(std::isnan(Coordinate{ 0, 0 }.getAngle().value)) << "Angle of 0,0 is not defined";
	}

	TEST(CoordinateTest, Equal) {
		constexpr Coordinate Base{ 4, 4 };
		EXPECT_TRUE(coordinateEqual(Base, Base)) << "Equal to itself";
		EXPECT_TRUE(coordinateEqual(Coordinate{ 4,4 }, Base)) << "Equal to a coordinate with the same values";
		constexpr Coordinate Other{ 0, 7 };
		EXPECT_FALSE(coordinateEqual(Other, Base)) << "Coordinates 1 and 2 not equal";
		EXPECT_FALSE(coordinateEqual(Coordinate{ 4, -4 }, Base)) << "Not equal to a coordinate with a different Y value";
		EXPECT_FALSE(coordinateEqual(Coordinate{ -4, 4 }, Base)) << "Not equal to a coordinate with a different X value";
	}

	TEST(CoordinateTest, Rotate) {
		constexpr Coordinate Base{ 4, 4 };
		EXPECT_TRUE(coordinateEqual(Coordinate{ 4, -4 }, Base.rotated(-M_PI / 2))) << "Rotate OK";
	}

	TEST(CoordinateTest, Translate) {
		constexpr Coordinate Base{ 4, 4 };
		EXPECT_TRUE(coordinateEqual(Coordinate{ 0, 16 }, Base.translated({ -4, 12 }))) << "Translate OK";
	}

	TEST(CoordinateTest, Scale) {
		constexpr Coordinate Base{ 4, 4 };
		EXPECT_TRUE(coordinateEqual(Coordinate{ 0.5, 8 }, Base.scaled({ 0.125, 2 }))) << "Scaled OK";
	}

	TEST(CoordinateTest, Reciprocal) {
		constexpr Coordinate Base{ 0.5, 8 };
		EXPECT_TRUE(coordinateEqual(Coordinate{ 2, 0.125 }, Base.getReciprocal())) << "Reciproke OK";
	}
}