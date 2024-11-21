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

#include <gtest/gtest.h>
#include "Matrix.h"
#include <Windows.h>
#include <psapi.h>

#include "CartesianEllipse.h"
#include "EllipseFit.h"
#include "SolverMatrix.h"
#include "MathUtils.h"

namespace EllipseMathTest {
    using EllipseMath::EllipseFit;
    using EllipseMath::CartesianEllipse;
    using EllipseMath::Coordinate;
    using EllipseMath::Angle;

    long long getMemoryUsage() {
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            return pmc.WorkingSetSize;
        }
        return 0;
    }

    TEST(MemTest, test1) {
        constexpr int tests = 1000000;
        long long startMem = getMemoryUsage();
        for (int test = 0; test < tests; test++) {
            // start the fitter
            EllipseFit ellipseFit;
            ellipseFit.begin();

            // create test data generator
            constexpr auto Center = Coordinate{ 1, 2 };
            constexpr auto Radius = Coordinate{ 10, 6 };
            constexpr auto XAxisAngle = Angle{ M_PI / 3 };
            const auto inputEllipse = CartesianEllipse(Center, Radius, XAxisAngle);
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
                printf(" Expected buffer to be full, but it wasn't\n");
            }
            else {
                const auto resultQuadraticEllipse = ellipseFit.fit();

                // Result should be equal to the parameters of the test data generator
                const auto result = CartesianEllipse(resultQuadraticEllipse);
            }
        }
        long long endMem = getMemoryUsage();



        std::cout << "Start: " << startMem << " End: " << endMem << std::endl;
        long long difference = std::llabs(startMem - endMem);
        std::cout << "Difference: " << difference << std::endl;
        EXPECT_TRUE(false) << "End";

    }
}
