#ifndef ELLIPSEFITTEST_H
#define ELLIPSEFITTEST_H

#include "gtest/gtest.h"
#include "CartesianEllipse.h"
#include "EllipseFit.h"

class EllipseFitTest : public ::testing::Test {
protected:
    QuadraticEllipse fitPerfectEllipse(EllipseFit& ellipseFit, const CartesianEllipse& inputEllipse);
    void assertPerfectEllipse(const Coordinate& center, const Coordinate& radius, const Angle& angle);
    void assertEllipseWithDistance(const Coordinate& center, const Coordinate& radius, const Angle& angle, const double& distance);
    void assertPartialEllipse(const CartesianEllipse& ellipse, const double& fraction, const double &startAngle);
};
#endif