#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
  Matrix(size_t r, size_t c);

  size_t get_rows() const;
  size_t get_cols() const;
  void set(size_t i, size_t j, int val);
  int get(size_t i, size_t j) const;
  void print(FILE *f) const;

  friend Matrix operator+(const Matrix& m1, const Matrix& m2);
  friend Matrix operator-(const Matrix& m1, const Matrix& m2);
  friend Matrix operator*(const Matrix& m1, const Matrix& m2);

  Matrix& operator+=(const Matrix& m);
  Matrix& operator-=(const Matrix& m);
  Matrix& operator*=(const Matrix& m);

  bool operator==(Matrix& m) const;
  bool operator!=(Matrix& m) const;
private:
  size_t _rows;
  size_t _cols;
  int **_data;
};

#endif
