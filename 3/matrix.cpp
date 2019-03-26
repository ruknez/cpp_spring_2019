#include "matrix.h"
#include <iostream>

Matrix::Array1::Array1() {
    pRow = nullptr;
}

Matrix::Array1::~Array1() {
    delete[] pRow;
}

const int& Matrix::Array1::operator[](int i) const {
    if (i >= cols) {
        throw std::out_of_range("");
        }
    return pRow[i];
}

int& Matrix::Array1::operator[] (int i) {
    if (i >= cols) {
        throw std::out_of_range("");
    }
    return pRow[i];
}


Matrix::Matrix(int rows_, int cols_) {

    matrix = new Array1 [rows_];

    rows = rows_;
    cols = cols_;

    for (int i = 0; i < rows_; i++) {
        matrix[i].cols = cols_;
        matrix[i].pRow = new int [cols];
    }

    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j++) {
            matrix[i].pRow[j] = 0;
        }
    }
}


Matrix::~Matrix() {
    delete[] matrix;
}

int Matrix::getRows() const {return rows;}

int Matrix::getColumns() const {return cols;}

const Matrix::Array1& Matrix::operator [] (const int index) const {
    if (index >= rows) {
        throw std::out_of_range("");
    }
    return matrix [index];
}

Matrix::Array1& Matrix::operator [] (int index) {
    if (index >= rows) {
        throw std::out_of_range("");
    }
    return matrix [index];
}


 bool Matrix::operator == (const Matrix& m) const {
    if (this == &m) {
         return true;
    }

    if (rows != m.getRows() || cols != m.getColumns()) {
        return false;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
           if (matrix[i].pRow[j] != m [i][j]) {
               return false;
           }
        }
    }
    return true;
 }
 
bool Matrix::operator != (const Matrix& m) const {
    if (rows != m.getRows() || cols != m.getColumns()) {
        return true;
    }

    return !(*this == m);
}

Matrix& Matrix::operator *= (const int num) {

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
           matrix[i].pRow[j] = matrix[i].pRow[j] * num;
        }
    }
    return *this;
}
