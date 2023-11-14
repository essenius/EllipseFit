#include <EllipseFit.h>
#include <CartesianEllipse.h>

void demoFit() {
    // start the fitter
    EllipseFit ellipseFit;
    ellipseFit.begin();

    // create test data generator
    const auto center = Coordinate{1, 2};
    const auto radius = Coordinate{10, 6};
    const auto angle = Angle{M_PI / 3};
    const auto inputEllipse = CartesianEllipse(center, radius, angle);
    const unsigned int pointsOnEllipse = EllipseFit::size();
    
    // feed the fitter with half an ellipse
    double currentAngle = 0;
    const double delta = M_PI / pointsOnEllipse;
    for (unsigned int i = 0; i < pointsOnEllipse; i++) {
      Coordinate point = inputEllipse.getParametricRepresentation(Angle{currentAngle});
      ellipseFit.addMeasurement(point);
      currentAngle += delta;
    }
    
    // execute the fitting
    if (!ellipseFit.bufferIsFull()) {
      Serial.println("  Expected buffer to be full, but it wasn't");
    } else {
      const auto resultQuadraticEllipse = ellipseFit.fit();
      
      // Result should be equal to the parameters of the test data generator
      const auto result = CartesianEllipse(resultQuadraticEllipse);
      Serial.printf("  Result:\n   Center (%f, %f)\n   Radius (%f, %f)\n   Angle %f\n", result.center.x, result.center.y, result.radius.x, result.radius.y, result.angle.value);     
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