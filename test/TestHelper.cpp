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

#include <gtest/gtest.h>
#include "TestHelper.h"

#include "MathUtils.h"

using namespace EllipseMath;

namespace EllipseFitTest {

	void assertDoubleEqual(const double& a, const double& b, const std::string& label, const double& epsilon) {
		ASSERT_TRUE(isAboutEqual(a, b, epsilon)) << label << ": " << a << "!=" << b;
	}

	void assertCoordinatesEqual(const Coordinate& a, const Coordinate& b, const std::string& label, const double& epsilon) {
		assertDoubleEqual(a.x, b.x, label + std::string("(X)"), epsilon);
		assertDoubleEqual(a.y, b.y, label + std::string("(Y)"), epsilon);
	}

	void assertAnglesEqual(const Angle& a, const Angle& b, const std::string& label, const double& epsilon) {
		// avoid the asymptotes for tan
		if (isAboutEqual(b.value, M_PI / 2, epsilon) || isAboutEqual(b.value, -M_PI / 2, epsilon)) {
			assertDoubleEqual(a.value, b.value, label + "(asymptote)", epsilon);
		}
		else {
			// cater for differences of M_PI in the result which is OK for the tilt angle of an ellipse
			assertDoubleEqual(tan(a.value), tan(b.value), label + "(tan)", epsilon);
		}
	}
}
