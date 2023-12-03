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

#include <cmath>
#include "MathUtils.h"
#include "QuadraticEllipse.h"

// we use the base formula from https://mathworld.wolfram.com/CartesianEllipse.html: ax^2 + 2bxy + cy^2 + 2dx + 2fy + g = 0
// as that makes the math a bit simpler.
// we expect the constructor to deliver coordinates based on ax^2 + bxy + cy^2 + dx + fy + g = 0
// See also https://scipython.com/blog/direct-linear-least-squares-fitting-of-an-ellipse/

// we use a, b, c, d, f, g as Wolfram does that too - probably to not use e, which can cause confusion with the mathematical entity

QuadraticEllipse::QuadraticEllipse(const double& a1, const double& b1, const double& c1, const double& d1, const double& f1, const double& g1):
	a(a1), b(b1/2), c(c1), d(d1/2), f(f1/2), g(g1) {
	_discriminant = sqr(b) - a * c;
}

bool QuadraticEllipse::isValid() const {
	return _discriminant != 0;
}

Angle QuadraticEllipse::getAngle() const {
	if (b == 0) {  // NOLINT(clang-diagnostic-float-equal) -- avoiding division by 0
		return { (a < c ? 0 : M_PI / 2) };
	}
	auto baseAngle = 0.5 * atan2(2 * b, a - c) + M_PI / 2;
	if (baseAngle > M_PI / 2) baseAngle -= M_PI;
	return { baseAngle };
}

Coordinate QuadraticEllipse::getCenter() const {
	return { (c * d - b * f) / _discriminant, (a * f - b * d) / _discriminant };
}

Coordinate QuadraticEllipse::getRadius() const {
	const double numerator = 2 * (a * sqr(f) + c * sqr(d) + g * sqr(b) - 2 * b * d * f - a * c * g);
	const double partialDenominator = sqrt(sqr(a - c) + 4 * sqr(b));
	const double widthDenominator = _discriminant * (partialDenominator - (a + c));
	const double heightDenominator = _discriminant * (-partialDenominator - (a + c));
	Coordinate result;
	result.x = sqrt(numerator / widthDenominator);
	result.y = sqrt(numerator / heightDenominator);
	return result;
}
