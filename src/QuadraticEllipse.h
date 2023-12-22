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

// The fitting process delivers coefficients. This class translates those to coordinates (center, radius, and angle of main radius).

// ReSharper disable CppInconsistentNaming - following the naming convention of the coefficients in the ellipse equation

#ifndef QUADRATIC_ELLIPSE_H
#define QUADRATIC_ELLIPSE_H

#include "Coordinate.h"

namespace EllipseMath {

	class QuadraticEllipse {
	public:
		/**
		 * \brief Construct a QuadraticEllipse from the coefficients of the equation ax^2 + bxy + cy^2 + dx + fy + g = 0.
		 */
		QuadraticEllipse(const double& a1, const double& b1, const double& c1, const double& d1, const double& f1, const double& g1);

		QuadraticEllipse() = default;

		/**
		 * \returns the angle of the main radius of the ellipse
		 */
		Angle getAngle() const;

		/**
		 * \returns the center of the ellipse
		 */
		Coordinate getCenter() const;

		/**
		 * \returns the radius of the ellipse
		 */
		Coordinate getRadius() const;

		/**
		 * \returns whether the ellipse is valid
		 */
		bool isValid() const;

	private:
		double a{};
		double b{};
		double c{};
		double d{};
		double f{};
		double g{};
		double _discriminant;
	};
}
#endif