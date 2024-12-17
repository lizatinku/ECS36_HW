#include <gtest/gtest.h>
#include "qsort.cpp"

// Test case: Sorting an empty vector
TEST(QuickSortTest, SortWithGreater)
{
    std::vector<int> v{4, 2, 5, 1, 3};
    quick_sort(v.begin(), v.end(), std::greater<int>());
    std::vector<int> expected{5, 4, 3, 2, 1};
    ASSERT_EQ(v, expected);
}

// Test case: Sorting a vector with one element (already sorted)
TEST(QuickSortTest, SortVectorWithOneElement)
{
    std::vector<int> v{1};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1};
    ASSERT_EQ(v, expected);
}

// Test case: Sorting a vector with multiple elements (ascending order)
TEST(QuickSortTest, SortVectorWithMultipleElementsAscending)
{
    std::vector<int> v{3, 1, 2};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 2, 3};
    ASSERT_EQ(v, expected);
}

// Test case: Sorting a vector with multiple elements (descending order)
TEST(QuickSortTest, SortVectorWithMultipleElementsDescending)
{
    std::vector<int> v{1, 3, 2};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 2, 3};
    ASSERT_EQ(v, expected);
}

// Test case: Sorting a vector with negative and positive elements
TEST(QuickSortTest, SortVectorWithNegativeAndPositive)
{
    std::vector<int> v{-1, 3, -2, 0, 2};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{-2, -1, 0, 2, 3};
    ASSERT_EQ(v, expected);
}

// Test case: Sorting a vector with duplicate elements
TEST(QuickSortTest, SortVectorWithDuplicates)
{
    std::vector<int> v{3, 1, 2, 3, 2};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 2, 2, 3, 3};
    ASSERT_EQ(v, expected);
}

// Test case: Sorting a vector with large numbers
TEST(QuickSortTest, SortLargeNumbers)
{
    std::vector<int> v{1000000, 500000, 100000, 999999};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{100000, 500000, 999999, 1000000};
    ASSERT_EQ(v, expected);
}

// Test case: Sorting a vector in descending order using std::greater
TEST(QuickSortTest, SortDescending)
{
    std::vector<int> v{1, 3, 2};
    quick_sort(v.begin(), v.end(), std::greater<int>());
    std::vector<int> expected{3, 2, 1};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortEmpty)
{
    std::vector<int> v;
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected;
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortWithStringComparison)
{
    std::vector<std::string> v{"apple", "banana", "cherry", "date", "elderberry"};
    quick_sort(v.begin(), v.end(), std::less<std::string>());
    std::vector<std::string> expected{"apple", "banana", "cherry", "date", "elderberry"};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortWithStringComparisonReverse)
{
    std::vector<std::string> v{"apple", "banana", "cherry", "date", "elderberry"};
    quick_sort(v.begin(), v.end(), std::greater<std::string>());
    std::vector<std::string> expected{"elderberry", "date", "cherry", "banana", "apple"};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortAlreadySortedVector)
{
    std::vector<int> v{1, 2, 3, 4, 5};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 2, 3, 4, 5};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortReverseSortedVector)
{
    std::vector<int> v{5, 4, 3, 2, 1};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 2, 3, 4, 5};
    ASSERT_EQ(v, expected);
}
