#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <string>
#include "../src/MathUtils.h"
#include "../src/Coordinate.h"

void assertDoubleEqual(const double& a, const double& b, const std::string& label, const double& epsilon = EPSILON);
void assertCoordinatesEqual(const Coordinate& a, const Coordinate& b, const std::string& label, const double& epsilon = EPSILON);
void assertAnglesEqual(const Angle& a, const Angle& b, const std::string& label, const double& epsilon = EPSILON);

#endif