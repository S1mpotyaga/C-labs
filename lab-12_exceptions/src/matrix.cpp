#include "matrix.h"

#include <iostream>
#include <fstream>

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

void Matrix::deleteSelf() {
	for (size_t i = 0; i < _rows; i++) {
		delete[] _data[i];
	} 
	delete[] _data;
}

Matrix::~Matrix() {
	deleteSelf();
}

void Matrix::load(std::string s) {
	std::ifstream in(s.c_str(), std::ifstream::in);
	if (!in.good())
		throw MatrixException("LOAD: unable to open file.");

	MatrixException formatException("LOAD: invalid file format");
	MatrixException memoryException("Unable to allocate memory.");
	
	size_t new_r = -1;
	if (!(in >> new_r)) {
		in.close();
		throw formatException;
	}
	size_t new_c = -1;
	if (!(in >> new_c)) {
		in.close();
		throw formatException;
	}

	int** newData = nullptr;
	
	try {
		newData = new int*[new_r];
	}
	catch (const std::exception& e) {
		throw memoryException;
	}
	for (size_t i = 0; i < new_r; i++) {
		try {
			newData[i] = new int[new_c];
		} catch (const std::exception& e) {
			for (size_t j = 0; j < i; j++) delete[] newData[j];
			delete[] newData;
			in.close();
			throw memoryException; 
		}
	}
	for (size_t i = 0; i < new_r; i++) {
		for (size_t j = 0; j < new_c; j++) {
			if (!(in >> newData[i][j])) {
				for (size_t k = 0; k < new_r; k++) delete[] newData[k];
				delete[] newData;
				in.close();
				throw formatException;
			}
		}
	}
	in.close();
	deleteSelf();
	_data = newData;
	_rows = new_r;
	_cols = new_c;
	for (size_t i = 0; i < new_r; i++) _data[i] = newData[i];
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

int Matrix::get(int i, int j) const {
	if (0 <= i && i <= (int)_rows && 0 <= j && j <= (int)_cols) {
		return _data[i][j];
	}
	throw MatrixException("ACCESS: bad index.");
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
        throw MatrixException("ADD: dimensions do not match.");
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
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
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

std::ostream& operator<< (std::ostream& out, const Matrix& m) {
	for (size_t i = 0; i < m.get_rows(); i++) {
		for (size_t j = 0; j < m.get_cols(); j++) {
			out << m.get(i, j);
			if (j + 1 != m.get_cols()) out << ' ';
		}
		out << '\n';
	}
	return out;
}

MatrixException::MatrixException(std::string s) {
	error = s;
}

const char* MatrixException::what() const noexcept {
	return error.c_str();
}