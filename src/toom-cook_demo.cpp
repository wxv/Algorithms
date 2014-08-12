#include <iostream>
#include "toom-cook.h"

int main()
{
    mpz_int f, g;
    mpz_ui_pow_ui(f.backend().data(), 3, 150000); // 3^150000, 71569 digits
    mpz_ui_pow_ui(g.backend().data(), 5, 100000); // 5^100000, 69898 digits

    mpz_int result = toom_cook(f, g);

    std::cout << result % 10000000000 << std::endl;

    return 0;
}
