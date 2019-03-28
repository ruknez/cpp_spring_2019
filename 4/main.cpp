#include "bigint.h"


int main () {

    BigInt a("1233131414123456");

    a.show();

    BigInt b = a;
    b.show();

    BigInt c = 923461997;
    c.show();

    BigInt d = 765431992;
    d = d + c;

    d.show ();
    return 0;
}
