#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

// Brute force find solution(s) to a^k + b^k + c^k + d^k = e^k, k = 5
// Current benchmarks:
// is_perfect_5: 8.2 s
// in_lookup: 2.5 s

typedef std::vector<long long> vll;

const int CUTOFF = 150;

bool in_lookup(const vll &l, long long n) // Lookup table method
{
    return std::find(l.begin(), l.end(), n) != l.end();
}

bool is_perfect_5(long long n) // Calculation method
{
    long long x = round(pow(n, 0.2));
    return x*x*x*x*x == n;
}

int main()
{
    vll lookup_5;

    for(long long i=1; i<1.5*CUTOFF; i++)
        lookup_5.push_back(i*i*i*i*i);



    for(long long a=1; a<CUTOFF; a++)
    {
        for(long long b=a; b<CUTOFF; b++)
        {
            std::cout << "a:" << a << " b:" << b << '\n';
            for(long long c=b; c<CUTOFF; c++)
            {
                for(long long d=c; d<CUTOFF; d++)
                {
                    long long e5 = a*a*a*a*a + b*b*b*b*b + c*c*c*c*c + d*d*d*d*d;
                    if (in_lookup(lookup_5, e5))
                    {
                        std::cout<<a<<"^5 + "<<b<<"^5 + "<<c<< "^5 + "<<d<<"^5 = "<<
                        int(pow(e5, 0.2)) << "^5";
                        goto stop;
                    }
                }
            }
        }
    }


    stop:



    return 0;
}
