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

// CartesianEllipse supports the following calculations based on a (fitted) QuadraticEllipse
// * the distance between a point an the ellipse
// * the coordinates of a point projected on the ellipse
// * the coordinate of the parametric representation of the ellipse given an angle
// * an approximation of the circumference of the circle
//
// These methods are used to determine whether we have an outlier: too far away from the ellipse => outlier

#ifndef CARTESIAN_ELLIPSE_H
#define CARTESIAN_ELLIPSE_H

#include "Angle.h"
#include "QuadraticEllipse.h"
#include "Coordinate.h"

class CartesianEllipse {
public:

	CartesianEllipse() = default;
	CartesianEllipse(const Coordinate& center, const Coordinate& radius, const Angle& angle);
	explicit CartesianEllipse(const QuadraticEllipse& quadraticEllipse);

	/** 
	* \returns an approximation of the circumference of the ellipse
	*/
	double getCircumference() const;

	/**
	* \returns the distance between the ellipse and a point
	*/
	double getDistanceFrom(const Coordinate& referencePoint) const;

	/**
	* \returns the point on the ellipse for a given angle (relative to the center of the ellipse, not the origin)
	*/
	Coordinate getPointOnEllipseAtAngle(const Angle& referenceAngle) const;

	/**
	* \returns the point on the ellipse closest to a given point
	*/
	Coordinate getPointOnEllipseClosestTo(const Coordinate& referencePoint) const;

	/**
	* \returns whether the ellipse is valid
	*/
	bool isValid() const;

// compromise between encapsulation and testability: make the data members protected so we can expose them in a driver subclass
protected:
	QuadraticEllipse _coefficient{};
	Coordinate _center{};
	Coordinate _radius{};
	Angle _angle{};
	bool _hasData = false;

};
#endif
