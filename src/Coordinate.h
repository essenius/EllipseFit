// Copyright 2021-2023 Rik Essenius
// 
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
// except in compliance with the License. You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.

// Various calculations for coordinates, which are the basis for more complex calcuations in e.g. ellipses

#ifndef COORDINATE_H
#define COORDINATE_H
#include "Angle.h"

struct Coordinate {
	double x;
	double y;

	Coordinate operator-() const;

	bool operator==(const Coordinate& other) const;

	/**
	 * \return the angle between the coordinate and the origin
	 */
	Angle getAngle() const;

	/**
	 * \return the angle between the coordinate and another coordinate
	 */
	Angle getAngleFrom(const Coordinate& other) const;

	/**
	 * \return the distance between the coordinate and the origin
	 */
	double getDistance() const;

	/**
	 * \return the distance between the coordinate and another coordinate
	 */
	double getDistanceFrom(const Coordinate& other) const;

	/**
	 * \return the reciprocal of the coordinate (1/x, 1/y)
	 */
	Coordinate getReciprocal() const;

	/**
	 * \return the coordinate rotated over an angle
	 */
	Coordinate rotated(double angle) const;

	/**
	 * \return the coordinate scaled with another coordinate
	 */
	Coordinate scaled(const Coordinate& vector) const;

	/**
	 * \return the coordinate translated with another coordinate
	 */
	Coordinate translated(const Coordinate& vector) const;
};
#endif
