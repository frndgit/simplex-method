#include "Matrix.hpp"

real_t Matrix::Trace() const {
	if(!Square()) {
		throw std::runtime_error("Matrix::Trace need a square matrix.");
	}

	real_t sum = 0;
	for(size_t i = 0; i < Height(); ++i)
		sum += grid_[i][i];

	return sum;
}

real_t Matrix::Det() const {
	if(!Square()) {
		throw std::runtime_error("Matrix::Det need a square matrix.");
	}

	try {
		std::pair <Matrix, Matrix> LU = LUDecomposition(*this);
		real_t det = 1;
		for(const auto &m : {LU.first, LU.second}) {
			for(size_t d = 0; d < m.Width(); ++d)
				det *= m[d][d];
		}
		return det;
	} catch(std::runtime_error e) {
		return 0;
	}
}
