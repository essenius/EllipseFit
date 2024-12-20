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

#include "EllipseFit.h"
#include "QuadraticEllipse.h"
#include <iostream>

namespace EllipseMath {
	// see https://autotrace.sourceforge.net/WSCG98.pdf for an explanation of the algorithm
	// optimized version of https://github.com/mericdurukan/ellipse-fitting

	// fixed buffer size as we don't want to fragment the heap
	constexpr unsigned int EllipseFit::BufferSize;  // NOLINT(readability-redundant-declaration, clang-diagnostic-deprecated-redundant-constexpr-static-def) -- using C++ 11 on device

	EllipseFit::EllipseFit() {
		// Calculating the constant vectors/matrices once to save a bit of time when fitting
		const Matrix c1({ {0, 0, 2},{ 0, -1, 0},{ 2, 0, 0} });
		_c1Inverse = c1.inverted();
		_design2.setColumn(2, 1); // set the last column to all ones
	}

	bool EllipseFit::addMeasurement(const double x, const double y) {
		if (_pointCount >= BufferSize) return false;
		// Design matrix (D in the article). Building up incrementally to minimize compute at fit
		_design1(_pointCount, 0) = x * x;
		_design1(_pointCount, 1) = x * y;
		_design1(_pointCount, 2) = y * y;
		_design2(_pointCount, 0) = x;
		_design2(_pointCount, 1) = y;
		_pointCount++;
		return true;
	}

	bool EllipseFit::addMeasurement(const Coordinate& point) {
		return addMeasurement(point.x, point.y);
	}

	void EllipseFit::begin() {
		_pointCount = 0;
	}

	QuadraticEllipse EllipseFit::fit() const {

		// Scatter matrix (S in the article)
		const Matrix scatter1 = _design1.transposed<Matrix>() * _design1;
		const Matrix scatter2 = _design1.transposed<Matrix>() * _design2;
		const Matrix scatter3 = _design2.transposed<Matrix>() * _design2;

		if (!scatter3.isInvertible()) {
			// if the scatter matrix is not invertible, we can't fit an ellipse
			return QuadraticEllipse();
		}

		// reduced scatter matrix (M in the article)
		const auto reducedScatter = SolverMatrix(_c1Inverse * (scatter1 - scatter2 * scatter3.inverted() * scatter2.transposed<Matrix>()));

		const auto eigenvectors = reducedScatter.getEigenvectors();

		// 4ac - b^2 must be positive for an ellipse
		Array condition = 4.0 * (eigenvectors.getRow(0) * eigenvectors.getRow(2)) - eigenvectors.getRow(1).pow2();

		// a1 and a2 are the coefficients: a1 = (a,b,c), a2 = (d,f,g).
		Matrix a1(3, 1);

		// there should be one where the condition is positive, that's the one we need

		auto found = false;
		for (Dimension eigenVectorIndex = 0; eigenVectorIndex < condition.columnCount(); eigenVectorIndex++) {
			if (condition(0, eigenVectorIndex) > 0) {
				a1 = Matrix(eigenvectors.getColumn(eigenVectorIndex));
				found = true;
				break;
			}
		}

		// this could happen if the data doesn't represent an ellipse, e.g. a straight line
		if (!found) {
			return { 0, 0, 0, 0, 0, 0 };
		}

		const auto a2 = -1 * scatter3.inverted() * scatter2.transposed<Matrix>() * a1;

		return { a1(0,0), a1(1,0), a1(2,0), a2(0,0), a2(1,0), a2(2,0) };
	}
}