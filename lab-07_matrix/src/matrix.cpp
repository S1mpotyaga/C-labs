#include "matrix.h"

#include <stdexcept>

Matrix::Matrix(size_t r, size_t c) {
	_rows = r;
	_cols = c;
	_data = new int*[_rows];
	for (size_t i = 0; i < _rows; i++) {
		_data[i] = new int[_cols];
		for (size_t j = 0; j < _cols; j++) {
			_data[i][j] = 0;
		}
	}
}

size_t Matrix::get_rows() const {
	return _rows;
}

size_t Matrix::get_cols() const{
	return _cols;
}

void Matrix::set(size_t i, size_t j, int val) {
	if (i <= _rows && j <= _cols) {
		_data[i][j] = val;
	} else {
		throw std::runtime_error("Indexes out of range");
	}
}

int Matrix::get(size_t i, size_t j) const {
	if (i <= _rows && j <= _cols) {
		return _data[i][j];
	}
	throw std::runtime_error("Indexes out of range");
	return 0;
}

void Matrix::print(FILE* f) const {
	for (size_t i = 0; i < _rows; i++) {
		for (size_t j = 0; j < _cols; j++) {
			fprintf(f, "%d", _data[i][j]);
			fprintf(f, " ");
		}
		fprintf(f, "\n");
	}
}

Matrix operator+ (const Matrix& m1, const Matrix& m2) {
	if (m1._rows != m2._rows || m1._cols != m2._cols) 
		throw new std::runtime_error("Sizes of summands are not equal");
	size_t r = m1._rows;
	size_t c = m1._cols;
	Matrix m(r, c);
	for (size_t i = 0; i < r; i++) {
		for (size_t j = 0; j < c; j++) 
			m.set(i, j, m1.get(i, j) + m2.get(i, j));
	}
	return m;
}

Matrix operator- (const Matrix& m1, const Matrix& m2) {
	if (m1._rows != m2._rows || m1._cols != m2._cols) 
		throw new std::runtime_error(
			"Sizes of subtrahend are not equal to sizes of minuend");
	size_t r = m1._rows;
	size_t c = m1._cols;
	Matrix m(r, c);
	for (size_t i = 0; i < r; i++) {
		for (size_t j = 0; j < c; j++) 
			m.set(i, j, m1.get(i, j) - m2.get(i, j));
	}
	return m;
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
	if (m1._cols != m2._rows) 	
		throw new std::runtime_error(
			"Incorrect sizes in multiply");
	size_t r = m1._rows;
	size_t c = m2._cols;
	Matrix m(r, c);
	int sum = 0;
	for (size_t i = 0; i < r; i++) {
		for (size_t j = 0; j < c; j++) {
			sum = 0;
			for (size_t k = 0; k < m1._cols; k++) {
				sum += m1.get(i, k) * m2.get(k, j);
			}
			m.set(i, j, sum);
		}
	}
	return m;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	return *this = *this + m;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	return *this = *this - m;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	return *this = *this * m;
}

bool Matrix::operator==(Matrix& m) const{
	if (_rows != m.get_rows() || _cols != m.get_cols()) return false;
	for (size_t i = 0; i < _rows; i++) {
		for (size_t j = 0; j < _cols; j++) {
			if (_data[i][j] != m.get(i, j)) return false;
		}
	}
	return true;
}

bool Matrix::operator !=(Matrix& m) const{
	return !(*this == m);
}