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

#include <EllipseFit.h>
#include <CartesianEllipse.h>
#include <MathUtils.h>

using namespace EllipseMath;

void demoFit() {
    // start the fitter
    EllipseFit ellipseFit;
    ellipseFit.begin();

    // create test data generator
    const auto center = Coordinate{ 1, 2 };
    const auto radius = Coordinate{ 10, 6 };
    const auto angle = Angle{ M_PI / 3 };
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
        Serial.println("  Expected buffer to be full, but it wasn't");
    }
    else {
        const auto resultQuadraticEllipse = ellipseFit.fit();

        // Result should be equal to the parameters of the test data generator
        const auto result = CartesianEllipse(resultQuadraticEllipse);
        Serial.printf("  Result:\n   Center (%f, %f)\n   Radius (%f, %f)\n   Angle %f\n", result.getCenter().x, result.getCenter().y, result.getRadius().x, result.getRadius().y, result.getAngle().value);
    }
}

void setup() {
  Serial.begin(115200);
  delay(10);
  demoFit(); 
}

void loop() {
   // nothing to do, waiting forever.
}