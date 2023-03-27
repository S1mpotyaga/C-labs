#include "matrix.hpp"

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

Matrix::Matrix(const Matrix& m) {
	_rows = m._rows;
	_cols = m._cols;
	_data = new int*[_rows];
	for (size_t i = 0; i < _rows; i++) {
		_data[i] = new int[_cols];
		for (size_t j = 0; j < _cols; j++) {
			_data[i][j] = m._data[i][j];
		}
	}
}

Matrix::~Matrix() {
	for (size_t i = 0; i < _rows; i++) {
		delete[] _data[i];
	} 
	delete[] _data;
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (*this == m) return *this;
	
	for (size_t i = 0; i < _rows; i++) 
		delete[] _data[i];
	delete [] _data;

	_rows = m._rows;
	_cols = m._cols;
	_data = new int*[_rows];	
	for (size_t i = 0; i < _rows; i++) {
		_data[i] = new int[_cols];
		for (size_t j = 0; j < _cols; j++) 
			_data[i][j] = m._data[i][j]	;
	}
	return *this;
}

size_t Matrix::get_rows() const {
	return _rows;
}

size_t Matrix::get_cols() const{
	return _cols;
}

void Matrix::set(size_t i, size_t j, int val) {
	if (i < _rows && j < _cols) {
		_data[i][j] = val;
	} else {
		throw std::runtime_error("Indices out of range");
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
			if (j != _cols - 1) fprintf(f, " ");
		}
		fprintf(f, "\n");
	}
}

Matrix Matrix::operator+(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols) {
        throw std::runtime_error("Sizes are different");
    }
 
    Matrix answer(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            answer._data[i][j] = _data[i][j] + m._data[i][j];
        }
    }
 
    return answer;
}
 
Matrix Matrix::operator-(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols) {
        throw std::runtime_error("Sizes are different");
    }
 
    Matrix answer(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            answer.set(i, j, _data[i][j] - m.get(i, j));
        }
    }
 
    return answer;
}
 
Matrix Matrix::operator*(const Matrix& m) const {
    if (_cols != m._rows) {
        throw std::runtime_error("Sizes do not match");
    }
 
    Matrix answer(_rows, m._cols);
    for (size_t i = 0; i < answer._rows; i++) {
        for (size_t j = 0; j < answer._cols; j++) {
            int sum = 0;
            for (size_t t = 0; t < _cols; ++t) {
                sum += _data[i][t] * m.get(t, j);
            }
            answer.set(i, j, sum);
        }
    }
 
    return answer;
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

bool Matrix::operator==(const Matrix& m) const {
    if (this == &m) {
        return true;
    }
 
    if (_rows != m._rows || _cols != m._cols) {
        return false;
    }
 
    for (size_t row = 0; row < _rows; ++row) {
        for (size_t col = 0; col < _cols; ++col) {
            if (_data[row][col] != m.get(row, col)) {
                return false;
            }
        }
    }
 
    return true;
}

bool Matrix::operator!=(const Matrix& m) const {
    return !(*this == m);
}