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

inline mpz_int lshift(mpz_int n, int b)
{
    mpz_int result;
    mpz_mul_2exp(result.backend().data(), n.backend().data(), b);
    return result;
}

inline mpz_int rshift(mpz_int n, int b)
{
    mpz_int result;
    mpz_tdiv_q_2exp(result.backend().data(), n.backend().data(), b);
    return result;
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
mpz_int toom_3(mpz_int m, mpz_int n)
{
    // naive is broken
    const bool use_naive = false;

    mpz_int threshold;
    mpz_ui_pow_ui(threshold.backend().data(), 2, 1000); // 2^1000
    if (m < threshold && n < threshold)
        return m * n;

    const int k = 3; // Toom-3
    const int b = 1073741824; // 2^30, radix (large value)

    int i = std::max(mpz_log(m,b)/k, mpz_log(n,b)/k) + 1; // Int division
    mpz_int B;
    mpz_ui_pow_ui(B.backend().data(), b, i); // B = b^i

    mpz_int m0 = m % B; // First base B digits
    mpz_int m1 = (m/B) % B; // Next base B digits
    mpz_int m2 = m/B/B; // Leftover
    mpz_int n0 = n % B;
    mpz_int n1 = (n/B) % B;
    mpz_int n2 = n/B/B;

    // p(x) = m2*x^2 + m1*x + m0
    // q(x) = n2*x^2 + n1*x + n0
    // Using points 0, 1, -1, -2, infinity
    if (use_naive)
    {
        mpz_int p_0, p_1, p_neg1, p_neg2, p_inf, q_0, q_1, q_neg1, q_neg2, q_inf;
        p_0 = m0;                   q_0 = n0;
        p_1 = m0 + m1 + m2;         q_1 = n0 + n1 + n2;
        p_neg1 = m0 - m1 + m2;      q_neg1 = n0 - n1 + n2;
        p_neg2 = m0 - 2*m1 + 4*m2;  q_neg2 = n0 - 2*n1 + 4*n2;
        p_inf = m2;                 q_inf = n2;


        // Pointwise multiplication
        mpz_int r_0 = toom_3(p_0, q_0);
        mpz_int r_1 = toom_3(p_1, q_1);
        mpz_int r_neg1 = toom_3(p_neg1, q_neg1);
        mpz_int r_neg2 = toom_3(p_neg2, q_neg2);
        mpz_int r_inf = toom_3(p_inf, q_inf);

        // Solving matrix equations by multiplying by inverted matrix
        mpz_int r0 = r_0;
        mpz_int r1 = r_0/2  + r_1/3     - r_neg1    + r_neg2/6  - 2*r_inf;
        mpz_int r2 = -r_0   + r_1/2     + r_neg1/2              - r_inf;
        mpz_int r3 = -r_0/2 + r_1/6     + r_neg1/2  - r_neg2/6  + 2*r_inf;
        mpz_int r4 =                                                r_inf;


        return r0 + B*r1 + B*B*r2 + B*B*B*r3 + B*B*B*B*r4;
    }
    else
    {
        // (C) 2007-2011 Marco Bodrato
        // http://www.bodrato.it/toom-cook/bt-3way-z-2.gp
        mpz_int W0, W1, W2, W3, W4;

        // 5*2 add/sub, 2 shift; 5mul (n)
        W3 = m0 + m2        ; W2 = n0 + n2  ;
        W0 = W3 - m1        ; W4 = W2 - n1  ;
        W3 = W3 + m1        ; W2 = W2 + n1  ;

        W1 = toom_3(W3, W2) ; W2 = toom_3(W0, W4);

        W0 = lshift(W0 + m2, 1) - m0; W4 = lshift(W4 + n2, 1) - n0;

        W3 = toom_3(W0, W4);

        W0 = toom_3(m0, n0);        ; W4 = toom_3(m2, n2);
        // Interpolation: 8 add/sub, 3 shift, 1 Sdiv (2n)
        W3 =(W3 - W1)/3;
        W1 =rshift(W1 - W2, 1);
        W2 = W2 - W0;
        W3 =rshift(W2 - W3, 1) + lshift(W4, 1);
        W2 = W2 + W1;
        // Early recomposition:
        W3 = W4*B + W3;
        W1 = W2*B + W1;
        W1 = W1 - W3;
        // Final recomposition:
       return W3*B*B*B + W1*B + W0;
    }
}

mpz_int toom_4(mpz_int m, mpz_int n);
// Future?

#endif // TOOM
