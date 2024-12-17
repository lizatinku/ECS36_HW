#ifndef QSORT_CPP
#define QSORT_CPP

#include "qsort.hpp"
#include <algorithm>
#include <iterator>
#include <random>
using namespace std;

template <typename RandomAccessIter, typename Comparator>
void quick_sort(RandomAccessIter first, RandomAccessIter last, Comparator comparator)
{
    // Sorting the range
    if (first == last || distance(first, last) <= 1)
        return;

    // Randomized pivot selection using rand()
    RandomAccessIter pivot_iter = first + (rand() % distance(first, last));

    iter_swap(pivot_iter, prev(last)); // Move the pivot to the last position

    auto pivot = *prev(last);
    RandomAccessIter i = first;

    for (RandomAccessIter j = first; j != prev(last); ++j)
    {
        if (comparator(*j, pivot)) // Comparator determines order
        {
            iter_swap(i, j);
            ++i;
        }
    }
    iter_swap(i, prev(last)); // Place the pivot in its correct position

    // Recursive sorting of subranges
    quick_sort(first, i, comparator);
    quick_sort(next(i), last, comparator);
}

#endif
