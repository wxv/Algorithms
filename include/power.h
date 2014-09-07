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
            result = (result * base) % mod;

        base = (base * base) % mod;
        power >>= 1;
    }

    return result;
}




#endif // POWER_H
