#include "Matrix.hpp"

Matrix::val_t Matrix::Trace() const {
	if(!Square()) {
		throw std::runtime_error("Matrix::Trace need a square matrix.");
	}

	val_t sum = 0;
	for (size_t i = 0; i < Height(); ++i)
		sum += grid_[i][i];

	return sum;
}

Matrix::val_t Matrix::Det() const {
	if(!Square()) {
		throw std::runtime_error("Matrix::Det need a square matrix.");
	}

	try {
		std::tuple <Matrix, Matrix, Matrix> LUP = LUPDecomposition(*this);
		Matrix::val_t det = 1;
		for (const auto &m : {std::get<0>(LUP), std::get<1>(LUP)}) {
			for(size_t d = 0; d < m.Width(); ++d)
				det *= m[d][d];
		}
		return det;
	} catch(std::runtime_error e) {
		return 0;
	}
}
