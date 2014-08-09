#include <boost/multiprecision/gmp.hpp>
#include <iostream>

using namespace boost::multiprecision;

namespace boost{ namespace multiprecision{

class gmp_int;

typedef number<gmp_int >         mpz_int;

}}


// Karatsuba's O(n^(log_2(3))) algorithm
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

// GMP does not have logarithm??
inline int mpz_log(mpz_int z, int base)
{
    int count = 0;
    while (z >= base) // floor(log)
    {
        z /= base;
        ++count;
    }
    return count;
}

// Toom-3 based on Wikipedia's implementation
mpz_int toom_cook(mpz_int m, mpz_int n)
{
    mpz_int threshold;
    mpz_ui_pow_ui(threshold.backend().data(), 2, 1000);
    if (m < threshold and n < threshold)
    {
        return m * n;
    }

    int k = 3; // Toom-3
    int b = 10000; // Radix (large value)

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

    mpz_int r_0 = p_0 * q_0;
    mpz_int r_1 = p_1 * q_1;
    mpz_int r_neg1 = p_neg1 * q_neg1;
    mpz_int r_neg2 = p_neg2 * q_neg2;
    mpz_int r_inf = p_inf * q_inf;

    // Solving matrix equations (see README)
    // Multiply by inverted matrix

    mpz_int r0 = r_0;
    mpz_int r1 = r_0/2  + r_1/3 - r_neg1    + r_neg2/6  + r_inf;
    mpz_int r2 = -r_0   + r_1/2 + r_neg1/2              - r_inf;
    mpz_int r3 = -r_0/2 + r_1/6 + r_neg1/2  - r_neg2/6  + 2*r_inf;
    mpz_int r4 =                                        r_inf;



    return r0 + B*r1 + B*B*r2 + B*B*B*r3 + B*B*B*B*r4;
}

int main()
{
    // 120 digit multiplicands
    const mpz_int x("461516004148971847450687728295051520819348189617713693620405"
                    "788622839733880667131021616145113142692185715868681960426769");
    const mpz_int y("396661689878051280981368038664785226063044063812328363811774"
                    "037291571915163134758418523492009331471439729019296250138507");
    // x * y = 183065718111...73609080493883


    // mpz_int m("1234567890123456789012");
    // mpz_int n("987654321987654321098");



    std::cout << toom_cook(x, y) << std::endl;


    return 0;
}

