// Copyright 2024 Rik Essenius
// 
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
// except in compliance with the License. You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.

#include <EllipseFit.h>
#include <CartesianEllipse.h>
#include <MathUtils.h>

#include <gtest/gtest.h>

using namespace EllipseMath;

namespace EllipseFitTest {

    // copy to examples/EllipseFitDemo when changed

    TEST(EllipseFitDemo, Demo) {
        // start the fitter
        EllipseFit ellipseFit;
        ellipseFit.begin();

        // create test data generator
        constexpr auto center = Coordinate{ 1, 2 };
        constexpr auto radius = Coordinate{ 10, 6 };
        constexpr auto angle = Angle{ M_PI / 3 };
        const auto inputEllipse = CartesianEllipse(center, radius, angle);
        const unsigned int pointsOnEllipse = EllipseFit::getSize();

        // feed the fitter with half an ellipse
        double currentAngle = 0;
        const double delta = M_PI / pointsOnEllipse;
        for (unsigned int i = 0; i < pointsOnEllipse; i++) {
            Coordinate point = inputEllipse.getPointOnEllipseAtAngle(Angle{ currentAngle });
            ellipseFit.addMeasurement(point);
            currentAngle += delta;
        }

        // execute the fitting
        if (!ellipseFit.bufferIsFull()) {
            printf("  Expected buffer to be full, but it wasn't\n");
        }
        else {
            const auto resultQuadraticEllipse = ellipseFit.fit();

            // Result should be equal to the parameters of the test data generator
            const auto result = CartesianEllipse(resultQuadraticEllipse);
            printf("  Result:\n   Center (%f, %f)\n   Radius (%f, %f)\n   Angle %f\n", result.getCenter().x, result.getCenter().y, result.getRadius().x, result.getRadius().y, result.getAngle().value);
        }
    }

}