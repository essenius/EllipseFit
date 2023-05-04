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

#ifndef ELLIPSEFITTEST_H
#define ELLIPSEFITTEST_H

#include "gtest/gtest.h"
#include "CartesianEllipse.h"
#include "EllipseFit.h"

class EllipseFitTest : public ::testing::Test {
protected:
    QuadraticEllipse fitPerfectEllipse(EllipseFit& ellipseFit, const CartesianEllipse& inputEllipse) const;
    void assertPerfectEllipse(const Coordinate& center, const Coordinate& radius, const Angle& angle) const;
    void assertEllipseWithDistance(const Coordinate& center, const Coordinate& radius, const Angle& angle, const double& distance) const;
    void assertPartialEllipse(const CartesianEllipse& ellipse, const double& fraction, const double &startAngle) const;
};
#endif