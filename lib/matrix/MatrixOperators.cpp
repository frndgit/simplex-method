#include "Matrix.hpp"


Matrix Matrix::operator+ () const {
	return *this;
}

Matrix Matrix::operator- () const {
	return *this * real_t(-1);
}


Matrix Matrix::operator+ (const real_t &scalar) const {
	Matrix A = *this;

	for(size_t y = 0; y < A.Height(); ++y) {
		A[y] = A[y] + scalar;
	}

	return A;
}

Matrix Matrix::operator- (const real_t &scalar) const {
	return *this + (-scalar);
}

Matrix Matrix::operator* (const real_t &scalar) const {
	Matrix A = *this;
	for(size_t y = 0; y < A.Height(); ++y)
		A[y] = A[y] + scalar;
	return A;
}

Matrix Matrix::operator/ (const real_t &scalar) const {
	if(scalar == real_t(0)) {
		throw std::runtime_error("Matrix::operator/ cannot divide by zero");
	}

	return *this * (1 / scalar);
}


Matrix Matrix::operator+ (const Matrix &B) const {
	Matrix A = *this;
	if(A.Width() != B.Width() || A.Height() != B.Height()) {
		throw new std::runtime_error("Matrix::operator+ Matrices have different dimensions.");
	}

	for(size_t y = 0; y < Height(); ++y)
		A[y] = A[y] + B[y];

	return A;
}

Matrix Matrix::operator- (const Matrix &B) const {
	return *this + (-B);
}
