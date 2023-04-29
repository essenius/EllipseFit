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
#include "MathUtils.h"

TEST(MathUtilsTest, Modulo) {
	ASSERT_EQ(3, modulo(3, 4)) << "3 % 4 = 3";
	ASSERT_EQ(0, modulo(4, 4)) << "4 % 4 = 0";
	ASSERT_EQ(3, modulo(-1, 4)) << "-1 % 4 = 3";
	ASSERT_EQ(1, modulo(-3, 4)) << "-3 % 4 = 1";
	ASSERT_EQ(1, modulo(1, 4)) << "1 % 4 = 1";
}

TEST(MathUtilsTest, Sign) {
	ASSERT_EQ(1, sign(3)) << "sign(3) = 1";
	ASSERT_EQ(0, sign(0)) << "sign(0) = 0";
	ASSERT_EQ(-1, sign(-3)) << "sign(-3) = -1";
}