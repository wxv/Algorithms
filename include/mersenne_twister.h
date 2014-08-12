#ifndef MERSENNE_TWISTER_H
#define MERSENNE_TWISTER_H

#include <time.h>

/* Mersenne Twister is a widely used PRNG. It provides fast generation of high
 * quality pseudo-random integers. Based on Wikipedia's pseudocode.
 * The following is MT19937, with a period of 2^19937 - 1.
 */

 unsigned int MT[624];  // Array for generator
 int index = 0;

void initialize_generator(int seed)
{
    MT[0] = seed;
    for(int i=1; i<624; i++)
    {
        MT[i] = ((1812433253 * MT[i-1]) ^ ((MT[i-1] >> 30) + i)) & 0xFFFFFFFF;
    }
}

// Extract a tempered number from [0, 2^32 - 1] based on index value
// Call generate_numbers() every 624 numbers
unsigned int extract_number()
{
    void generate_numbers();
    if (index == 0)
    {
        generate_numbers();
    }
    unsigned int y = MT[index];
    y ^= y >> 11;
    y ^= (y << 7) & 2636928640;
    y ^= (y << 15) & 4022730752;
    y ^= 18;

    index = (index + 1) % 624;
    return y;
}

// Generate an array of 624 untempered numbers
void generate_numbers()
{
    for(int i=0; i<624; i++)
    {
        unsigned int y = (MT[i] & 0x80000000) + (MT[(i+1)%624] & 0x7FFFFFFF);
        MT[i] = MT[(i + 397) % 624] ^ (y >> 1);
        if (y % 2)
        {
            MT[i] ^= 2567483615;
        }
    }
}

#endif // MERSENNE_TWISTER_H
