# EllipseFit

Fit a series of data points to an ellipse. This was originally designed to track magnetic fields in a water meter reader
and with that be able to count pulses corresponding to water usage.

## Configuration and structure

This library is designed to be usable both in the Arduino IDE as well as in a C++ project. It is structured as follows:

- `src/` contains the source files (this is where Arduino IDE expects them)
- `test/` contains the test cases
- `examples/` contains an example sketch for Arduino
- `keywords.txt` contains the keywords for the Arduino IDE
- `library.properties` contains the library properties for the Arduino IDE
- To be able to compile the library in a C++ project under CMake, `CMakeLists.txt` files are included. These files are not used by the Arduino IDE.
	CMake also uses the `lib\` folder (which is not used by the Arduino IDE).
- Visual Studio uses `EllipseFit.sln` as well as the `*.vcxproj` files in the folders `src/` and `test/`. `vcpkg` is used to install dependencies. `vcpkg` is configured to use
	`vcpkg.json` and `vcpkg-configuration.json` to find the library. These files are not used by the Arduino IDE (or when using CMake directly).

This library depends on the [rix-matrix](https://github.com/essenius/Matrix) library which provides basic matrix operations.
Initially the [Eigen](https://eigen.tuxfamily.org) library was used, but that library is too large to be used effctively in an Arduino project.

## Classes/structures

All classes are in the `EllipseFit` namespace.

### Angle

Modeling an angle (in radians)

- `sin()`, `cos()`: sine and cosine of the angle
- `getQuadrant()`: returns the quadrant of the angle (1-4)
- `degreesTimesTen()`: angle in degrees * 10, so we can store it in an integer and keep reasonable accuracy.
- `operator-`: subtract right from left (right can be a double or another angle)

### CartesianEllipse

Calculation of various ellipse characteristics based on center, radius and angle.

- constructors that can use  either center, radius and angle or a QuadraticEllipse
- `coefficient`: QuadraticEllipse
- `center`: Coordinate of the center
- `radius`: Coordinate representing the length of both radii
- `angle`: Angle of the ellipse
- `getCircumference()`: An approximation of the circumference of the ellipse
- `getDistanceFrom(Coordinate)`: The distance of a point from the ellipse
- `getPointOnEllipseAtAngle(Angle)`: The point on the ellipse at the given angle (relative to center of	ellipse)
- `getPointOnEllipseClosestTo(Coordinate)`: The point on the ellipse closest to the given point
- `isValid()`: whether the ellipse is valid (i.e. not a line or a point)

### Coordinate

2 dimensional point/vector. 

- `getAngle()`: the angle between the coordinate and the origin
- `getAngleFrom(Coordinate)`: the angle between the coordinate and the given coordinate
- `getDistance()`: the distance between the coordinate and the origin
- `getDistanceFrom(Coordinate)`: the distance between the coordinate and the given coordinate
- `getReciprocal()`: the reciprocal of the coordinate (1/x, 1/y)
- `rotated(Angle)`: the coordinate rotated by the given angle
- `scaled(Coordinate)`: the coordinate scaled by the given coordinate
- `translated(Coordinate)`: the coordinate translated by the given coordinate

### EllipseFit

The main class. It has a fixed size	buffer of measurements and can fit those to an ellipse.

- `addMeasurement(x, y)`: enter measurement.
- `addMeasurement(Coordinate)`: enter measurement.
- `begin()`: initialize the buffer.
- `bufferIsFull()` check when the buffer is filled up. 
- `fit()`: when the buffer is full, call this method to execute a fit. It returns a `QuadraticEllipse`. If it cannot fit the data to an ellipse, it returns all zeroes as coordinates. Before using the outcome, use the `isValid()` method of `QuadraticEllipse` to validate that the fit succeeded.
- `getPointCount()`: the number of points in the buffer
- `getSize()`: the size of the buffer

### MathUtils

A couple of math utilities that are used by multiple classes:

- `isAboutEqual(a, b, epsilon)`: whether two doubles are about equal up to epsilon
- `sqr(a)`: square of a number
- `modulo(a, b)`: modulo of a number, but with a positive result (i.e. -1 % 3 = 2)
- `sign(a)`: sign of a number (-1, 0 or 1)

### QuadraticEllipse

An ellipse specified by coordinates.

- The constructor expects parameters `a`, `b`, `c`, `d`, `f` and `g` of the formula `ax^2 + bxy + cy^2 + dx + fy + g = 0`.
Internally it converts this to the [Wolfram formula](https://mathworld.wolfram.com/QuadraticCurve.html): `ax^2 + 2bxy + cy^2 + 2dx + 2fy + g = 0` as that makes the math a bit simpler.
- `getAngle()`: the angle of the main radius of the ellipse
- `getCenter()`: the center of the ellipse
- `getRadius()`: the radii of the ellipse
- `isValid()` to check whether the parameters result in a valid ellipse (implemented by checking if the discriminant is not equal to 0)
