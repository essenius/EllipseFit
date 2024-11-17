// Copyright 2023-2024 Rik Essenius
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

using namespace EllipseMath;

namespace EllipseFitTest {

	void expectDoubleEqual(const double& a, const double& b, const std::string& label, const double& epsilon) {
		EXPECT_TRUE(isAboutEqual(a, b, epsilon)) << label << ": " << a << "!=" << b;
	}

	void expectCoordinatesEqual(const Coordinate& a, const Coordinate& b, const std::string& label, const double& epsilon) {
		expectDoubleEqual(a.x, b.x, label + std::string("(X)"), epsilon);
		expectDoubleEqual(a.y, b.y, label + std::string("(Y)"), epsilon);
	}

	void expectAnglesEqual(const Angle& a, const Angle& b, const std::string& label, const double& epsilon) {
		// avoid the asymptotes for tan
		if (isAboutEqual(b.value, M_PI / 2, epsilon) || isAboutEqual(b.value, -M_PI / 2, epsilon)) {
			expectDoubleEqual(a.value, b.value, label + "(asymptote)", epsilon);
		}
		else {
			// cater for differences of M_PI in the result which is OK for the tilt angle of an ellipse
			expectDoubleEqual(tan(a.value), tan(b.value), label + "(tan)", epsilon);
		}
	}
}
