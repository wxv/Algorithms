#include <iostream>
#include "lcg.h"
#include "time.h"

int main()
{
    int seed = time(NULL);

    int x = lcg_glibc(seed);
    for(int i=0; i<100; i++)
    {
        x = lcg_glibc(x); // Replace with whatever implementation
    }
    std::cout << x << std::endl;

    return 0;
}
