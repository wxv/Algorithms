#ifndef POWER_H
#define POWER_H

// Exponentiation by squaring

long long pow(int base, int power)
{
    long long result = 1;
    while (power)
    {
        if (power & 1)
            result *= base;

         base *= base;
        power >>= 1;
    }

    return result;
}

int powm(int base, int power, int mod)
{
    int result = 1;
    while (power)
    {
        if (power & 1)
            // Prevent overflow
            result = ((long long)result * (long long)base) % mod;

        base = ((long long)base * (long long)base) % mod;
        power >>= 1;
    }

    return result;
}




#endif // POWER_H
