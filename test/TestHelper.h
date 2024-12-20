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

#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <string>
#include "MathUtils.h"
#include "Coordinate.h"

namespace EllipseFitTest {
	using EllipseMath::Coordinate;
	using EllipseMath::Angle;
	using EllipseMath::Epsilon;

	void expectDoubleEqual(const double& a, const double& b, const std::string& label, const double& epsilon = Epsilon);
	void expectCoordinatesEqual(const Coordinate& a, const Coordinate& b, const std::string& label, const double& epsilon = Epsilon);
	void expectAnglesEqual(const Angle& a, const Angle& b, const std::string& label, const double& epsilon = Epsilon);

}
#endif