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

namespace EllipseMath {

	CartesianEllipse::CartesianEllipse(const Coordinate& center, const Coordinate& radius, const Angle& angle) :
		_center(center), _radius(radius), _angle(angle), _hasData(true) {}

	CartesianEllipse::CartesianEllipse(const QuadraticEllipse& quadraticEllipse) : _coefficient(quadraticEllipse), _hasData(true) {
		_center = _coefficient.getCenter();
		_radius = _coefficient.getRadius();
		_angle = _coefficient.getAngle();
	}

	double CartesianEllipse::getCircumference() const {

		// approximation, not so easy to determine precisely.
		// See https://www.johndcook.com/blog/2013/05/05/ramanujan-circumference-ellipse/
		const auto t = 3 * sqr((_radius.x - _radius.y) / (_radius.x + _radius.y));
		return M_PI * (_radius.x + _radius.y) * (1 + t / (10 + sqrt(4 - t)));
	}

	double CartesianEllipse::getDistanceFrom(const Coordinate& referencePoint) const {
		return getPointOnEllipseClosestTo(referencePoint).getDistanceFrom(referencePoint);
	}

	Coordinate CartesianEllipse::getPointOnEllipseAtAngle(const Angle& referenceAngle) const {
		// Note the angle is relative to the center of the ellipse, not the origin 
		return Coordinate{
			_center.x + _radius.x * cos(referenceAngle.value) * cos(_angle.value) -
			_radius.y * sin(referenceAngle.value) * sin(_angle.value),
			_center.y + _radius.y * sin(referenceAngle.value) * cos(_angle.value) +
			_radius.x * cos(referenceAngle.value) * sin(_angle.value)
		};
	}

	Coordinate CartesianEllipse::getPointOnEllipseClosestTo(const Coordinate& referencePoint) const {
		// Normalize the point, then find the angle with the origin. This gives the angle that parametricRepresentation needs.
		const auto transformedCoordinate = referencePoint
			.translated(-_center)
			.rotated(-_angle.value)
			.scaled(_radius.getReciprocal());
		const auto angleWithOrigin = transformedCoordinate.getAngle();
		return getPointOnEllipseAtAngle(angleWithOrigin);
	}

	bool CartesianEllipse::isValid() const {
		return _radius.x > 0 && _radius.y > 0;
	}
}