#ifndef LCG_H
#define LCG_H

/* Linear congruential generators with common implementations. */

const int bitmask = 0x7fff0000; // bits 30-16
const int mod_2_31 = 0x7FFFFFFF; // bitmask for mod 2^31

int lcg_borland(int seed)
{
    unsigned int x = 22695477 * seed + 1; // mod 2^32
    return (x & bitmask) >> 16;
}

int lcg_glibc(int seed)
{
    return (1103515245 * seed + 12345) & mod_2_31;
}

int lcg_ansi_c(int seed)
{
    unsigned int x = (1103515245 * seed + 12345) & mod_2_31;
    return (x & bitmask) >> 16;
}

int lcg_microsoft_visual(int seed)
{
    unsigned int x = (214013 * seed + 2531011) & mod_2_31;
    return (x & bitmask) >> 16;
}

#endif // LCG_H
