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

// Mathematical angle (in radians)

#ifndef HEADER_ANGLE
#define HEADER_ANGLE

#include <cstdint>

namespace EllipseFit {

	struct Angle {
		double value;

		/**
		 * \return the cosine of the angle
		 */
		double cos() const;

		/**
		 * \return the angle in degrees * 10 (to avoid floating point)
		 */
		int16_t degreesTimes10() const;

		Angle operator-(const Angle& other) const;

		double operator-(const double& other) const;

		/**
		* \return the quadrant of the angle (1, 2, 3 or 4)
		*/
		unsigned int getQuadrant() const;

		/**
		 * \return the normalized angle in radians (between -PI and	PI)
		 */
		static double normalized(const double& value);

		/**
		* \return the sine of the angle
		*/
		double sin() const;
	};
}
#endif
