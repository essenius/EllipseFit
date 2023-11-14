// Copyright 2023 Rik Essenius
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

#include "Coordinate.h"
#include "MathUtils.h"

bool coordinateEqual(const Coordinate& a, const Coordinate& b) {
	return a == b;
}

TEST(CoordinateTest, AngleDistance) {
	constexpr Coordinate BASE{ 4, 4 };
	ASSERT_DOUBLE_EQ(M_PI / 4, BASE.getAngle().value) << "Angle OK";
	ASSERT_DOUBLE_EQ(sqrt(32), BASE.getDistance()) << "Distance OK";
}

TEST(CoordinateTest, AngleFromDistanceFrom) {
	constexpr Coordinate BASE{ 4, 4 };
	ASSERT_DOUBLE_EQ(5, BASE.getDistanceFrom({ 0, 7 })) << "DistanceFrom OK";
	ASSERT_DOUBLE_EQ(-M_PI / 4, BASE.getAngleFrom({ -4, 12 }).value) << "AngleFrom OK";
}

TEST(CoordinateTest, AngleOfZeroIsNotDefined) {
	ASSERT_TRUE(isnan(Coordinate{ 0, 0 }.getAngle().value)) << "Angle of 0,0 is not defined";
}

TEST(CoordinateTest, Equal) {
	constexpr Coordinate BASE{ 4, 4 };
	ASSERT_TRUE(coordinateEqual(BASE, BASE)) << "Equal to itself";
	ASSERT_TRUE(coordinateEqual(Coordinate{ 4,4 }, BASE)) << "Equal to a coordinate with the same values";
	constexpr Coordinate OTHER{ 0, 7 };
	ASSERT_FALSE(coordinateEqual(OTHER,  BASE)) << "Coordinates 1 and 2 not equal";
	ASSERT_FALSE(coordinateEqual(Coordinate{ 4, -4 }, BASE)) << "Not equal to a coordinate with a different Y value";
	ASSERT_FALSE(coordinateEqual(Coordinate{ -4, 4 }, BASE)) << "Not equal to a coordinate with a different X value";
}

TEST(CoordinateTest, Rotate) {
	constexpr Coordinate BASE{ 4, 4 };
	ASSERT_TRUE(coordinateEqual(Coordinate{ 4, -4 }, BASE.rotated(-M_PI / 2))) << "Rotate OK";
}

TEST(CoordinateTest, Translate) {
	constexpr Coordinate BASE{ 4, 4 };
	ASSERT_TRUE(coordinateEqual(Coordinate{ 0, 16 }, BASE.translated({-4, 12}))) << "Translate OK";
}

TEST(CoordinateTest, Scale) {
	constexpr Coordinate BASE{ 4, 4 };
	ASSERT_TRUE(coordinateEqual(Coordinate{ 0.5, 8 }, BASE.scaled({0.125, 2}))) << "Scaled OK";
}

TEST(CoordinateTest, Reciprocal) {
	constexpr Coordinate BASE{ 0.5, 8 };
	ASSERT_TRUE(coordinateEqual(Coordinate{ 2, 0.125 }, BASE.getReciprocal())) << "Reciproke OK";
}
