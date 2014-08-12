// Note: replaced "-" with "_" in define
#ifndef TOOM_COOK_H
#define TOOM_COOK_H

#include <boost/multiprecision/gmp.hpp>

using namespace boost::multiprecision;

namespace boost{ namespace multiprecision{

class gmp_int;

typedef number<gmp_int >         mpz_int;

}}


// GMP does not have logarithm?
inline int mpz_log(mpz_int z, int base) // floor(log)
{
    int count = 0;
    while (z >= base)
    {
        z /= base;
        ++count;
    }
    return count;
}

/* Toom-3 based on Wikipedia's implementation. Method of multiplying by splitting
 * up numbers into `k` parts (in this case, 3). In Toom-3, this reduces 9
 * multiplications to 5. The method used is described by Marco Bodrato. The digits
 * are split and turned into 2 polynomials. Then the polynomials are evaluated at
 * several points, the points are multiplied, and a new polynomial is interpolated
 * based on an inverted matrix. Finally the result is recomposed from the new
 * polynomial. Optimal matrices for `k` are described at
 * http://www.csd.uwo.ca/~eschost/Exam/WhatAboutToomCookMatricesOptimality.pdf
 */
mpz_int toom_cook(mpz_int m, mpz_int n)
{
    mpz_int threshold;
    mpz_ui_pow_ui(threshold.backend().data(), 2, 1000); // 2^1000
    if (m < threshold and n < threshold)
    {
        return m * n;
    }

    #define k 3 // Toom-3
    const int b = 1073741824; // 2^30, radix (large value)

    int i = std::max(mpz_log(m,b)/k, mpz_log(n,b)/k) + 1;
    mpz_int B;
    mpz_ui_pow_ui(B.backend().data(), b, i); // B = b^i

    mpz_int m0 = m % B; // First base B digits
    mpz_int m1 = (m/B) % B; // Next base B digits
    mpz_int m2 = (m/B/B) % B; // Leftover
    mpz_int n0 = n % B;
    mpz_int n1 = (n/B) % B;
    mpz_int n2 = (n/B/B) % B;

    // p(x) = m2*x^2 + m1*x + m0
    // q(x) = n2*x^2 + n1*x + n0
    // Using points 0, 1, -1, -2, infinity

    mpz_int p_0 = m0;
    mpz_int p_1 = m0 + m1 + m2;
    mpz_int p_neg1 = m0 - m1 + m2;
    mpz_int p_neg2 = m0 - 2*m1 + 4*m2;
    mpz_int p_inf = m2;

    mpz_int q_0 = n0;
    mpz_int q_1 = n0 + n1 + n2;
    mpz_int q_neg1 = n0 - n1 + n2;
    mpz_int q_neg2 = n0 - 2*n1 + 4*n2;
    mpz_int q_inf = n2;

    // Pointwise multiplication
    mpz_int r_0 = toom_cook(p_0, q_0);
    mpz_int r_1 = toom_cook(p_1, q_1);
    mpz_int r_neg1 = toom_cook(p_neg1, q_neg1);
    mpz_int r_neg2 = toom_cook(p_neg2, q_neg2);
    mpz_int r_inf = toom_cook(p_inf, q_inf);

    // Solving matrix equations
    // Multiply by inverted matrix

    mpz_int r0 = r_0;
    mpz_int r1 = r_0/2 + r_1/3 - r_neg1 + r_neg2/6 + r_inf;
    mpz_int r2 = -r_0 + r_1/2 + r_neg1/2 - r_inf;
    mpz_int r3 = -r_0/2 + r_1/6 + r_neg1/2 - r_neg2/6 + 2*r_inf;
    mpz_int r4 = r_inf;


    return r0 + B*r1 + B*B*r2 + B*B*B*r3 + B*B*B*B*r4;
}

#endif // TOOM
