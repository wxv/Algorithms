#ifndef GCD_H
#define GCD_H

// Basic Euclidean algorithm
int euclid_gcd(int a, int b)
{
    while (b)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Iterative binary GCD algorithm
int binary_gcd(int a, int b)
{
    int shift;

    if (a == 0) return b;
    if (b == 0) return a;

    for (shift = 0; ((a | b) & 1) == 0; ++shift)
    {
        a >>= 1;
        b >>= 1;
    }
    while ((a & 1) == 0)
        a >>= 1;

    do
    {
        while ((b & 1) == 0)
            b >>= 1;

        if (a > b)
        {
            int t = b; b = a; a = t;
        }
        b = b - a;
    } while (b);

    return a << shift;
}



#endif
