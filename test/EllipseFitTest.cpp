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
#include "EllipseFitTest.h"
#include "TestHelper.h"

QuadraticEllipse EllipseFitTest::fitPerfectEllipse(EllipseFit& ellipseFit, const CartesianEllipse& inputEllipse) {
	const unsigned int pointsOnEllipse = EllipseFit::size();
	ellipseFit.begin();
	auto x = -M_PI;
	EXPECT_FALSE(ellipseFit.bufferIsFull()) << "Buffer is not full";
	for (unsigned int i = 0; i < pointsOnEllipse; i++) {
		EXPECT_EQ(i, ellipseFit.pointCount()) << "Point count " << i << " is correct";
		auto point = inputEllipse.parametricRepresentation(Angle{x});
		ellipseFit.addMeasurement(point);
		x += M_PI / (pointsOnEllipse / 2.0);
	}
	EXPECT_TRUE(ellipseFit.bufferIsFull()) << "Buffer is full";
	EXPECT_FALSE(ellipseFit.addMeasurement(0, 0)) << "Unable to add more points";
	return ellipseFit.fit();
}

void EllipseFitTest::assertPerfectEllipse(const Coordinate& center, const Coordinate& radius, const Angle& angle) {
	auto inputEllipse = CartesianEllipse(center, radius, angle);
	EllipseFit ellipseFit;
	const auto result = fitPerfectEllipse(ellipseFit, inputEllipse);
	EXPECT_TRUE(result.isValid()) << "Result is valid";
	const auto resultEllipse = CartesianEllipse(result);
	assertCoordinatesEqual(center, resultEllipse.center, "Center", EPSILON);
	assertCoordinatesEqual(radius, resultEllipse.radius, "Radius", EPSILON);
	if (fabs(radius.x - radius.y) > EPSILON) assertAnglesEqual(angle, resultEllipse.angle, "Angle", EPSILON);

	// check if all points of the parametric representation of the result ellipse are on the original ellipse
	auto x = -M_PI;
	for (int i = -16; i < static_cast<int>(EllipseFit::size()); i++) {
		Coordinate pointOut = resultEllipse.parametricRepresentation(Angle{x});
		const auto distanceFromEllipse = inputEllipse.distanceFrom(pointOut);
		assertDoubleEqual(0, distanceFromEllipse, "Distance", 0.0001);
		x += M_PI / (EllipseFit::size() / 2.0);
	}
}

// create two ellipses at a distance from the expected result, and add points from each to the fitter.

void EllipseFitTest::assertEllipseWithDistance(const Coordinate& center, const Coordinate& radius, const Angle& angle, const double& distance) {
	auto distancec = Coordinate{ distance, distance };
	const auto innerEllipse = CartesianEllipse(center, radius.translate(-distancec), angle);
	const auto outerEllipse = CartesianEllipse(center, radius.translate(distancec), angle);
	const unsigned int pointsOnEllipse = EllipseFit::size();
	EllipseFit ellipseFit;
	ellipseFit.begin();
	auto x = -M_PI;
	for (unsigned int i = 0; i < pointsOnEllipse; i++) {
		Coordinate point = i % 2 == 0
			? innerEllipse.parametricRepresentation(Angle{x})
			: outerEllipse.parametricRepresentation(Angle{x});
		ASSERT_TRUE(ellipseFit.addMeasurement(point)) << "Point " << x << " added";
		x += M_PI / (pointsOnEllipse / 2.0);
	}
	ASSERT_FALSE(ellipseFit.addMeasurement(0, 0)) << "Unable to add more points";

	const auto resultQuadraticEllipse = ellipseFit.fit();

	EXPECT_TRUE(resultQuadraticEllipse.isValid()) << "Result is valid";

	const auto resultEllipse = CartesianEllipse(resultQuadraticEllipse);

	x = -M_PI;
	assertCoordinatesEqual(center, resultEllipse.center, "Center", EPSILON);
	assertCoordinatesEqual(radius, resultEllipse.radius, "Radius", 0.01);
	if (fabs(radius.x - radius.y) > EPSILON) assertAnglesEqual(angle, resultEllipse.angle, "Angle", EPSILON);

	const auto middleEllipse = CartesianEllipse(center, radius, angle);

	for (int i = -16; i < static_cast<int>(pointsOnEllipse); i++) {
		Coordinate pointOut = resultEllipse.parametricRepresentation(Angle{x});
		assertDoubleEqual(0, middleEllipse.distanceFrom(pointOut), "Distance", 0.01);
		x += M_PI / (pointsOnEllipse / 2.0);
	}
}

void EllipseFitTest::assertPartialEllipse(const CartesianEllipse& ellipse, const double& fraction, const double &startAngle) {

	const unsigned int points = EllipseFit::size();
	EllipseFit ellipseFit;
	ellipseFit.begin();
	const double delta = M_PI * 2.0 * fraction / points;
	auto x = startAngle;
	for (unsigned int i = 0; i < points; i++) {
		Coordinate point = ellipse.parametricRepresentation(Angle{x});
		ASSERT_TRUE(ellipseFit.addMeasurement(point)) << "Point " << x << " added";
		x += delta;
	}
	ASSERT_FALSE(ellipseFit.addMeasurement(0, 0)) << "Unable to add more points";

	const auto resultQuadraticEllipse = ellipseFit.fit();

	EXPECT_TRUE(resultQuadraticEllipse.isValid()) << "Result is valid";
	
	const auto resultEllipse = CartesianEllipse(resultQuadraticEllipse);

	// we need to accept a bit more variation here 
	constexpr double EPSILON1 = 0.01;
	assertCoordinatesEqual(ellipse.center, resultEllipse.center, "Center", EPSILON1);
	assertCoordinatesEqual(ellipse.radius, resultEllipse.radius, "Radius", EPSILON1);
	if (fabs(ellipse.radius.x - ellipse.radius.y) > EPSILON) assertAnglesEqual(ellipse.angle, resultEllipse.angle, "Angle", EPSILON1);

	x = -M_PI;
	constexpr int POINTS_ON_ELLIPSE = 32;
	for (int i = -16; i < POINTS_ON_ELLIPSE; i++) {
		Coordinate pointOut = resultEllipse.parametricRepresentation(Angle{x});
		assertDoubleEqual(0, ellipse.distanceFrom(pointOut), "Distance", 0.001);
		x += M_PI / (POINTS_ON_ELLIPSE / 2.0);
	}
}

TEST_F(EllipseFitTest, PerfectFitCircle) {
	// Circle with center = (100, -100), radius=(8,8), angle = irrelevant
	assertPerfectEllipse({ 100, -100 }, { 8, 8 }, { 0 });
}
TEST_F(EllipseFitTest, PerfectFitRoundEllipse) {
	// ellipse with center = (1,3), radius = (12,10), angle = pi/4, i.e. quite round
	assertPerfectEllipse({ 1, 3 }, { 12, 10 }, { M_PI / 4 });
}

TEST_F(EllipseFitTest, PerfectFitFlatEllipse) {
	// ellipse with center = (0,0), radius = (20,1), angle = pi/3, i.e. very flat ellipse
	assertPerfectEllipse({ 0, 0 }, { 20, 1 }, { M_PI / 3 });
}

TEST_F(EllipseFitTest, PerfectFitEllipseCloseToMeasured) {
	// ellipse with center = (-21.09,-45.71), radius = (12.68,9.88), angle = -0.48; close to one measured
	assertPerfectEllipse({ -21.09, -45.71 }, { 12.68, 9.88 }, { -0.48 });
}

TEST_F(EllipseFitTest, PerfectLineShouldNotFit) {
	auto inputEllipse = CartesianEllipse({0,0}, {10,0}, {M_PI / 3});
	EllipseFit ellipseFit;
	const auto result = fitPerfectEllipse(ellipseFit, inputEllipse);
	EXPECT_FALSE(result.isValid()) << "Samples forming a line should not return a match";
}

TEST_F(EllipseFitTest, FitWithDistance1) {
	assertEllipseWithDistance({ 0,0 }, { 10, 5 }, { -M_PI / 6 }, 0.1);
}

TEST_F(EllipseFitTest, FitWithDistance2) {
	assertEllipseWithDistance({ -30, -20 }, { 12, 9 }, { M_PI / 5 }, 0.1);
}

TEST_F(EllipseFitTest, PartialEllipseTest) {
	// take 30% of an ellipse, starting at M_PI/2
	assertPartialEllipse(CartesianEllipse({ 20,-20 }, { 10, 4 }, { M_PI / 5 }), 0.3, M_PI / 2);
}

TEST_F(EllipseFitTest, AllZeroSamples) {
	EllipseFit ellipseFit;
	ellipseFit.begin();
	ASSERT_EQ(32, ellipseFit.size()) << "Size OK";
	for (unsigned int i = 0; i < 32; i++) {
		ASSERT_TRUE(ellipseFit.addMeasurement(0, 0)) << "Point " << i << " added";
	}
	const auto resultQuadraticEllipse = ellipseFit.fit();
	EXPECT_FALSE(resultQuadraticEllipse.isValid()) << "Ellipse is not valid";
}


