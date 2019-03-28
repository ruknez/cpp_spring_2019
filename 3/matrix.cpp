
#include <iostream>

#include "matrix.h"
Matrix::Column::Column() {}

Matrix::Column::~Column() {
    delete[] pRow;
}

void Matrix::Column::SetParam (size_t cols_) {
   
    if (pRow == nullptr) {
        delete[] pRow;
    }
    pRow = new int [cols_];
    cols = cols_;

    for (size_t i = 0; i < cols; i++) {
        pRow[i] = 0;
    }

}

int Matrix::Column::GetNumber (size_t num) const {
    return pRow [num];
}

void Matrix::Column::SetNumber (size_t num, int val) {
    pRow[num] = val;
}

const int& Matrix::Column::operator[](size_t i) const {
    if (i >= cols) {
        throw std::out_of_range("");
        }
    return pRow[i];
}

int& Matrix::Column::operator[] (size_t i) {
    if (i >= cols) {
        throw std::out_of_range("");
    }
    return pRow[i];
}


Matrix::Matrix(size_t rows_, size_t cols_) {

    matrix = new Column [rows_];

    rows = rows_;
    cols = cols_;

    for (size_t i = 0; i < rows_; i++) {
        matrix[i].SetParam(cols);
    }
}

Matrix::~Matrix() {
    delete[] matrix;
}

size_t Matrix::getRows() const {return rows;}

size_t Matrix::getColumns() const {return cols;}

const Matrix::Column& Matrix::operator [] (const size_t index) const {
    if (index >= rows) {
        throw std::out_of_range("");
    }
    return matrix [index];
}

Matrix::Column& Matrix::operator [] (size_t index) {
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

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
           if (matrix[i].GetNumber(j) != m [i][j]) {
               return false;
           }
        }
    }
    return true;
 }
 
bool Matrix::operator != (const Matrix& m) const {

    return !(*this == m);
}

Matrix& Matrix::operator *= (const int num) {

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
           matrix[i].SetNumber(j, matrix[i].GetNumber(j) * num);// = matrix[i].pRow[j] * num;
        }
    }
    return *this;
}
