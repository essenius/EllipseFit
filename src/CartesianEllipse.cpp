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
#include <cstdio>
#include "CartesianEllipse.h"
#include "MathUtils.h"

CartesianEllipse::CartesianEllipse(const Coordinate& center, const Coordinate& radius, const Angle& angle): 
	center(center), radius(radius), angle(angle), hasData(true) {}

CartesianEllipse::CartesianEllipse(const QuadraticEllipse& quadraticEllipse): coefficient(quadraticEllipse), hasData(true) {
	center = coefficient.getCenter();
	radius = coefficient.getRadius();
	angle = coefficient.getAngle();
}

bool CartesianEllipse::fitSucceeded() const {
	return radius.getDistance() > EPSILON;
}

double CartesianEllipse::getCircumference() const {

	// approximation, not so easy to determine precisely.
	// See https://www.johndcook.com/blog/2013/05/05/ramanujan-circumference-ellipse/
    const auto t = 3 * sqr((radius.x - radius.y) / (radius.x + radius.y));
	return M_PI * (radius.x + radius.y) * (1 + t / (10 + sqrt(4 - t)));

}

Coordinate CartesianEllipse::getParametricRepresentation(const Angle& referenceAngle) const {
	// Note the angle is relative to the center of the ellipse, not the origin 
	return Coordinate {
		center.x + radius.x * cos(referenceAngle.value) * cos(angle.value) -
		radius.y * sin(referenceAngle.value) * sin(angle.value),
		center.y + radius.y * sin(referenceAngle.value) * cos(angle.value) +
		radius.x * cos(referenceAngle.value) * sin(angle.value)
	};
}

Coordinate CartesianEllipse::getPointOnEllipseFor(const Coordinate& referencePoint) const {
	// Normalize the point, then find the angle with the origin. This gives the angle that parametricRepresentation needs.
	const auto transformedCoordinate = referencePoint
		.translated(-center)
		.rotated(-angle.value)
		.scaled(radius.getReciprocal());
	const auto angleWithOrigin = transformedCoordinate.getAngle();
	return getParametricRepresentation(angleWithOrigin);
}

double CartesianEllipse::getDistanceFrom(const Coordinate& referencePoint) const {
	return getPointOnEllipseFor(referencePoint).getDistanceFrom(referencePoint);
}
