#ifndef SORT_H
#define SORT_H

#include <vector>
#include <algorithm>

typedef std::vector<int> v_int;

v_int bubble_sort(v_int v)
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

v_int quick_sort(v_int v, int left, int right)
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
//HEAP SORT -----------------------------------------------

v_int shift_right(v_int v, int low, int high)
{
    int root = low;
    while ((root*2)+1 <= high)
    {
        int left_child = (root * 2) + 1;
        int right_child = left_child + 1;
        int swapx = root;

        if (v[swapx] < v[left_child])
            swapx = left_child;

        if ((right_child <= high) && (v[swapx] < v[right_child]))
            swapx = right_child;

        if (swapx != root)
        {
            std::swap(v[root], v[swapx]);
            root = swapx;
        }
        else break;
    }
    return v;
}

v_int heapify(v_int v, int low, int high)
{
    int midx = (high - low - 1)/2;
    while (midx >= 0)
    {
        v = shift_right(v, midx, high);
        --midx;
    }
    return v;
}

v_int heap_sort(v_int v)
{
    int v_size = v.size();
    v = heapify(v, 0, v_size-1);
    int high = v_size - 1;
    while (high > 0)
    {
        std::swap(v[high], v[0]);
        --high;
        v = shift_right(v, 0, high);
    }
    return v;
}

v_int insertion_sort(v_int v)
{
    for (int i=1; i<v.size(); i++)
    {
        int x = v[i];
        int j = i-1;
        while (j >= 0 && v[j] > x)
        {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = x;
    }
    return v;
}

#endif // SORT_H
