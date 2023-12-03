#ifndef CARTESIANELLIPSEDRIVER_H
#define CARTESIANELLIPSEDRIVER_H

#include "CartesianEllipse.h"

class CartesianEllipseDriver : public CartesianEllipse {
public:
	explicit CartesianEllipseDriver(const QuadraticEllipse& quadraticEllipse) : CartesianEllipse(quadraticEllipse) {}
	explicit CartesianEllipseDriver(const Coordinate& center, const Coordinate& radius, const Angle& angle) :
		CartesianEllipse(center, radius, angle) {}

	using CartesianEllipse::_angle;
	using CartesianEllipse::_center;
	using CartesianEllipse::_radius;
};

#endif