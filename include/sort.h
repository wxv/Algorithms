#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>

std::vector<int> bubble_sort(std::vector<int> v)
{
    bool swapped = true;
    int n = v.size();
    while (swapped)
    {
        swapped = false;
        for(int i=1; i<n; i++)
        {
            if (v[i-1] > v[i])
            {
                std::swap(v[i-1], v[i]);
                swapped = true;
            }
        }
        n--;
    }
    return v;
}

std::vector<int> quick_sort(std::vector<int> v, int left, int right)
{
    int i = left;
    int j = right;
    int pivot = v[(left + right) / 2];

    while (i <= j)
    {
        while (v[i] < pivot)
            i++;
        while (v[j] > pivot)
            j--;
        if (i <= j)
        {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        v = quick_sort(v, left, j);
    if (i < right)
        v = quick_sort (v, i, right);

    return v;
}



#endif // SORT_H
