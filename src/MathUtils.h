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

// Utilities for variables of type double that we need at multiple places

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#ifdef _WIN32
// ReSharper disable once CppUnusedIncludeDirective - on purpose, to get M_PI defined.
// And we don't want this conditional include proliferate.
#include <corecrt_math_defines.h>
#endif

namespace EllipseMath {

	constexpr double Epsilon = 1e-4;

	/**
	 * \returns whether two doubles are about equal (up to a given epsilon)
	 */
	bool isAboutEqual(const double& a, const double& b, const double& epsilon = Epsilon);

	/**
	 * \returns the square of a double
	 */
	double sqr(const double& a);

	/**
	 * \returns	a modulo b, but with a positive result (unlike the % operator)
	 */
	int modulo(int a, int b);

	/**
	 * \returns the sign of a number (-1, 0, or 1)
	 */
	double sign(const double& a);
}
#endif
