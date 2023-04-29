# EllipseFit

Fit a series of data points to an ellipse. This was originally designed to track magnetic fields in a water meter reader
and with that be able to count pulses corresponding to water usage.

## Angle

Modeling the angle of the ellipse with respect to the X axis (in radians)

## CartesianEllipse

Calculation of various ellipse characteristics based on center, radius and angle.
Can approximate circumference, and calculate parametric representation, whether a point is on it, and the distance 
of a point from the ellipse.

## Coordinate

2 dimensional point/vector. Can calculate differences, angles, distances, and can rotate, translate, scale, and invert

## EllipseFit

The main class. Call `begin()` to initialize. Enter measurements via `addMeasurement`. The class has a fixed buffer size and the method `bufferIsFull()` can be used
to check when it filled up. Once that is the case,  call the `fit()` method, which returns a `QuadraticEllipse`. 
If it cannot fit the data to an ellipse, it returns all zeroes as coordinates.
Before using the outcome, use the `isValid()` method of `QuadraticEllipse` to validate that the fit succeeded.

## MathUtils

A couple of math utilities that are used by multiple classes

## QuadraticEllipse

An ellipse specified by coordinates. The constructor expects parameters `a` to `g` to be based on the formula `ax^2 + bxy + cy^2 + dx + fy + g = 0`.
Internally it uses the [Wolfram formula](https://mathworld.wolfram.com/CartesianEllipse.html): `ax^2 + 2bxy + cy^2 + 2dx + 2fy + g = 0` as that makes the math a bit simpler.
It contains methods `angle()`, `center()` and `radius()` to calculate the corresponding characteristics of the ellipse, as well as a method `isValid()` to check whether the
parameters result in a valid ellipse (implemented by checking if the discriminant is not equal to 0)
