#include <iostream>
#include <cassert>

#include "matrix.h"

int main () {

    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);

    m[1][2] = 5; // строка 1, колонка 2
    double x = m[1][2];
   
    m *= 3; // умножение на число

    std::cout <<  x << std::endl;
    Matrix m1(rows, cols);

    m1[1][2] = 5;

    if (m1 == m) {
        std::cout << "m1 == m" << std:: endl;
    }

    return 0;
}