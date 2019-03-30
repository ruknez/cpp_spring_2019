#include <iostream>

#include "bigint.h"

int main () {

    BigInt a("1233131414123456");

    a.show();

    BigInt b = a;
    std::cout << b.show() << std::endl;

    BigInt c = 923461997;
    std::cout <<  c.show() << std::endl;

    BigInt d = 765431992;
    d = d + c;

    d = a + 1;

    a = 44444444;
    d = 88888887;


    std::cout << "d = " << d << "\na = " << a << std::endl;
    std::cout << "c = " << c << std::endl;
    
    a = d + c + a;

    std::cout << a << std::endl;
    if (a < d) {
        std::cout << "D < A \n";
    }
   // d.show ();
    return 0;
}
