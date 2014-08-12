#ifndef KARATSUBA_H
#define KARATSUBA_H

#include <boost/multiprecision/gmp.hpp>


using namespace boost::multiprecision;

namespace boost{ namespace multiprecision{

class gmp_int;

typedef number<gmp_int >         mpz_int;

}}


/* Karatsuba's O(n^(log_2(3))) algorithm
 * The first algorithm faster than the classical algorithm, reducing 4
 * multiplications to 3. Calculates with multiplication of numbers about
 * half the size along with addition, subtraction and shifting.
 */
mpz_int karatsuba(mpz_int x, mpz_int y)
{
    mpz_int threshold;
    mpz_ui_pow_ui(threshold.backend().data(), 2, 400); // 2^400
    if (x < threshold and y < threshold)
    {
        return x * y;
    }

    int m = std::max(msb(x), msb(y));
    int m2 = m / 2;

    mpz_int mask = 1;
    mask = (mask << m2) - 1;
    mpz_int xlow = x & mask;
    mpz_int ylow = y & mask;
    mpz_int xhigh = x >> m2;
    mpz_int yhigh = y >> m2;

    mpz_int a = karatsuba(xhigh, yhigh);
    mpz_int b = karatsuba(xlow + xhigh, ylow + yhigh);
    mpz_int c = karatsuba(xlow, ylow);
    mpz_int d = b - a - c;

    return (((a << m2) + d) << m2) + c;
}

#endif // KARATSUBA_H
