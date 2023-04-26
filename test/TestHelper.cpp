#include <gtest/gtest.h>
#include "TestHelper.h"

#include "../src/MathUtils.h"

void assertDoubleEqual(const double& a, const double& b, const std::string& label, const double& epsilon) {
	ASSERT_TRUE(aboutEqual(a, b, epsilon)) << label << ": " << a << "!=" << b;
}

void assertCoordinatesEqual(const Coordinate& a, const Coordinate& b, const std::string& label, const double& epsilon) {
	assertDoubleEqual(a.x, b.x, label + std::string("(X)"), epsilon);
	assertDoubleEqual(a.y, b.y, label + std::string("(Y)"), epsilon);
}

void assertAnglesEqual(const Angle& a, const Angle& b, const std::string& label, const double& epsilon) {
	// avoid the asymptotes for tan
	if (aboutEqual(b.value, M_PI/2, epsilon) || aboutEqual(b.value, -M_PI / 2, epsilon)) {
		assertDoubleEqual(a.value, b.value, label + "(asymptote)", epsilon);
	}
	else {
		// cater for differences of M_PI in the result which is OK for the tilt angle of an ellipse
		assertDoubleEqual(tan(a.value), tan(b.value), label + "(tan)", epsilon);
	}
}
