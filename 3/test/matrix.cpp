#include <iostream>


#include "matrix.h"

Matrix::Column::Column(int *ptr, size_t size) {
    std::cout << "I am in Column \n";
    
    pRow = ptr;
    cols = size;

    for (int i = 0; i < (int)size; i++) {
        std::cout << "pRow " << *(pRow + i ) << std::endl;
    }
}

Matrix::Column::~Column() {
    std::cout << "I am in dest Column \n";
    delete[] pRow;
}

Matrix::Column::Column (const Matrix::Column & copied) {
    std::cout << "Copy constr \n";
    pRow = copied.pRow;//new int [copied.cols];
    cols = copied.cols;

    for (int i = 0; i < (int)cols; i++) {
        std::cout << "pRow " << *(pRow + i ) << std::endl;
    }

   // std::copy (copied.pRow, copied.pRow + cols, pRow);
 }

int Matrix::Column::Getnumber (size_t num) const {
    return *(pRow + num);
}

void Matrix::Column::Changenumb (size_t num, int val) {
    *(pRow + num) = val;
}

const int& Matrix::Column::operator[](int i) const {
    if (i >= cols) {
        throw std::out_of_range("");
        }
    return pRow[i];
}

int& Matrix::Column::operator[] (int i) {
    if (i >= cols) {
        throw std::out_of_range("");
    }
    return pRow[i];
}


Matrix::Matrix(size_t rows_, size_t cols_) {
    rows = rows_;
    cols = cols_;
    
    matrix = new int [rows * cols];

    int count = 0;
    for (size_t i = 0; i < rows * cols; i++) {
        matrix[i] = count++;
    }

    for (size_t i = 0; i < rows * cols; i ++) {
        std::cout << matrix[i] << std::endl;
    }

    for (size_t i = 0; i < rows * cols; i += rows) {
        std::cout << matrix [i] << std::endl;
        ptr_to_clos.push_back ({&matrix[i], rows});
    }
}

Matrix::~Matrix() {
    delete[] matrix;
}

int Matrix::getRows() const {return rows;}

int Matrix::getColumns() const {return cols;}

const Matrix::Column& Matrix::operator [] (const int index) const {
    if (index >= rows) {
        throw std::out_of_range("");
    }
    return ptr_to_clos [index];
}

Matrix::Column& Matrix::operator [] (int index) {
    if (index >= rows) {
        throw std::out_of_range("");
    }
    return ptr_to_clos [index];
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
           if (ptr_to_clos[i].Getnumber(j) != m [i][j]) {
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
           ptr_to_clos[i].Changenumb(j, ptr_to_clos[i].Getnumber(j) * num);
        }
    }
    
    return *this;
}
