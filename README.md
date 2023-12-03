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

## Classes

### Angle

Modeling the angle of the ellipse with respect to the X axis (in radians)

### CartesianEllipse

Calculation of various ellipse characteristics based on center, radius and angle.
Can approximate circumference, and calculate parametric representation, whether a point is on it, and the distance 
of a point from the ellipse.

### Coordinate

2 dimensional point/vector. Can calculate differences, angles, distances, and can rotate, translate, scale, and invert

### EllipseFit

The main class. Call `begin()` to initialize. Enter measurements via `addMeasurement`. The class has a fixed buffer size and the method `bufferIsFull()` can be used
to check when it filled up. Once that is the case,  call the `fit()` method, which returns a `QuadraticEllipse`. 
If it cannot fit the data to an ellipse, it returns all zeroes as coordinates.
Before using the outcome, use the `isValid()` method of `QuadraticEllipse` to validate that the fit succeeded.

### MathUtils

A couple of math utilities that are used by multiple classes

### QuadraticEllipse

An ellipse specified by coordinates. The constructor expects parameters `a` to `g` to be based on the formula `ax^2 + bxy + cy^2 + dx + fy + g = 0`.
Internally it uses the [Wolfram formula](https://mathworld.wolfram.com/CartesianEllipse.html): `ax^2 + 2bxy + cy^2 + 2dx + 2fy + g = 0` as that makes the math a bit simpler.
It contains methods `angle()`, `center()` and `radius()` to calculate the corresponding characteristics of the ellipse, as well as a method `isValid()` to check whether the
parameters result in a valid ellipse (implemented by checking if the discriminant is not equal to 0)
