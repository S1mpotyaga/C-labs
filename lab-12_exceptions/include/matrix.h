#pragma once

#include <string>

class Matrix {
public:
    Matrix(size_t r = 0, size_t c = 0);
    Matrix(const Matrix& m);

    void deleteSelf();

    ~Matrix();

    void load(std::string s);
    
    size_t get_rows() const;
    size_t get_cols() const;
    void set(size_t i, size_t j, int val);
    int get(int i, int j) const;
    void print(FILE *f) const;

    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;

    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);

    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;



    Matrix& operator=(const Matrix& m);
private:
    size_t _rows;
    size_t _cols;
    int **_data;
};

std::ostream& operator<< (std::ostream& out, const Matrix& m);

class MatrixException : std::exception{
private:
    std::string error;
public:
    MatrixException(std::string s);

    virtual const char* what() const noexcept;
};

