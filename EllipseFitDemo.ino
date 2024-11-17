#include <EllipseFit.h>
#include <CartesianEllipse.h>

void demoFit() {
    using namespace EllipseMath;

    // start the fitter
    EllipseFit ellipseFit;
    ellipseFit.begin();

    // create test data generator
    constexpr auto Center = Coordinate{ 1, 2 };
    constexpr auto Radius = Coordinate{ 10, 6 };
    constexpr auto MainRadiusAngle = Angle{ M_PI / 3 };
    const auto inputEllipse = CartesianEllipse(Center, Radius, MainRadiusAngle);
    const unsigned int pointsOnEllipse = ellipseFit.getPointCount();

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
    // put your main code here, to run repeatedly:
}