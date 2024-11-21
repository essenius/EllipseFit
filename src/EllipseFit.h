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

// Fits a number of points to an ellipse. Uses the Eigen library which is quite large.
// Also it is quite a bit of work, so we optimize where we can to minimize calculations during fits, which need to complete within the time of a sample interval.  

#ifndef ELLIPSEFIT_H
#define ELLIPSEFIT_H

#include "Coordinate.h"
#include "QuadraticEllipse.h"
#include <SolverMatrix.h>

namespace EllipseMath {
	using RixMatrix::Array;
	using RixMatrix::Dimension;
	using RixMatrix::Matrix;
	using RixMatrix::SolverMatrix;

	class EllipseFit {

	public:
		explicit EllipseFit();

		/**
		 * \brief Add a point to the buffer
		 */
		bool addMeasurement(double x, double y);

		/**
		 * \brief Add a point to the buffer
		 */
		bool addMeasurement(const Coordinate& point);

		/**
		 * \brief Initialize a new fit
		 */
		void begin();

		/**
		 * \brief When the buffer is full, call this method to execute a fit.
		 * \returns the fitted ellipse
		 */
		QuadraticEllipse fit() const;

		/**
		 * \returns whether the buffer is full
		 */
		bool bufferIsFull() const { return _pointCount >= BufferSize; }

		/**
		 * \returns the number of points in the buffer
		 */
		unsigned int getPointCount() const { return _pointCount; }

		/**
		 * \returns the size of the buffer
		 */
		static unsigned int getSize() { return BufferSize; }

	private:
		static constexpr unsigned int BufferSize = 32;
		Matrix _c1Inverse{ 3, 3 };
		Matrix _design1{ BufferSize, 3 };
		Matrix _design2{ BufferSize, 3 };

		unsigned int _pointCount = 0;
	};
}
#endif
