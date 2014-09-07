#ifndef BINOMIAL_H
#define BINOMIAL_H

#include "gmpxx.h"

mpz_class mpz_bin(int n, int k)
{
    mpz_class result = n - k + 1;

    for(int i=2; i<=k; i++)
    {
        result *= n - k + i;
        mpz_divexact_ui(result.get_mpz_t(), result.get_mpz_t(), i);
    }

    return result;
}

long long ll_bin(int n, int k)
{
    long long result = n - k + 1;

    for(int i=2; i<=k; i++)
    {
        result *= n - k + i;
        result /= i;
    }

    return result;
}

#endif // BINOMIAL_H
