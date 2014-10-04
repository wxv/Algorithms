#include <vector>
#include <iostream>
#include "sort.h"

int main()
{
    std::vector<int> v = {1, 12, 5, 26, 7, 13, 9, -2};

    //std::vector<int> sorted = bubble_sort(v);
    std::vector<int> sorted = quick_sort(v, 0, v.size());

    for(size_t i=0; i<sorted.size(); i++)
    {
        std::cout << sorted[i] << " ";
    }

    return 0;
}
