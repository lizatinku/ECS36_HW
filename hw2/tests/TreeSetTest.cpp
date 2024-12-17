#include "TreeSet.cpp"
#include <gtest/gtest.h>

TEST(TreeSetTest, InstantiateEmptyTree)
{
    TreeSet<int> s{};

    ASSERT_EQ(s.size(), 0);
}

TEST(TreeSetTest, InstantiateTreeWithComparator)
{
    auto cmp = [](int a, int b)
    {
        if (a < b)
        {
            return 1;
        }
        else if (a > b)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    };
    TreeSet<int> s(cmp);

    ASSERT_EQ(s.size(), 0);

    s.add(1);
    s.add(2);
    s.add(3);
    s.add(4);
    ASSERT_EQ(s.to_vector(), std::vector<int>({4, 3, 2, 1}));
    ASSERT_EQ(s.min(), 4);
}

TEST(TreeSetTest, UnionTwo)
{
    TreeSet<int> s1({1, 2, 3, 4, 5});
    TreeSet<int> s2({3, 4, 5, 6, 7});
    TreeSet<int> s3 = s1 + s2;

    ASSERT_EQ(s3.size(), 7);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({1, 2, 3, 4, 5, 6, 7}));

    // union should not mutate original sets
    ASSERT_EQ(s1.size(), 5);
    ASSERT_EQ(s1.to_vector(), std::vector<int>({1, 2, 3, 4, 5}));
    ASSERT_EQ(s2.size(), 5);
    ASSERT_EQ(s2.to_vector(), std::vector<int>({3, 4, 5, 6, 7}));
}

TEST(TreeSetTest, Clear)
{
    TreeSet<int> s({1, 2, 3, 4, 5});
    s.clear();

    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.to_vector(), std::vector<int>({}));
}

TEST(TreeSetTest, Size)
{
    TreeSet<int> s({1, 2, 3});
    ASSERT_EQ(s.size(), 3);
}

TEST(TreeSetTest, IsEmpty)
{
    TreeSet<int> s;
    ASSERT_TRUE(s.is_empty());
    s.add(1);
    ASSERT_FALSE(s.is_empty());
}

TEST(TreeSetTest, AddElements)
{
    TreeSet<int> s;
    s.add(1);
    s.add(2);
    s.add(1);
    ASSERT_EQ(s.size(), 2);
    ASSERT_EQ(s.to_vector(), std::vector<int>({1, 2}));
}

TEST(TreeSetTest, Contains)
{
    TreeSet<int> s({1, 2, 3});
    ASSERT_TRUE(s.contains(2));
    ASSERT_FALSE(s.contains(5));
}

TEST(TreeSetTest, GetElement)
{
    TreeSet<int> s({1, 2, 3});
    ASSERT_EQ(s.get(2), std::optional<int>(2));
    ASSERT_EQ(s.get(4), std::nullopt);
}

TEST(TreeSetTest, MinMax)
{
    TreeSet<int> s({1, 2, 3});
    ASSERT_EQ(s.min(), 1);
    ASSERT_EQ(s.max(), 3);
}

TEST(TreeSetTest, Intersection)
{
    TreeSet<int> s1({1, 2, 3});
    TreeSet<int> s2({2, 3, 4});
    TreeSet<int> s3 = s1 & s2;
    ASSERT_EQ(s3.to_vector(), std::vector<int>({2, 3}));
}

TEST(TreeSetTest, Equality)
{
    TreeSet<int> s1({1, 2, 3});
    TreeSet<int> s2({1, 2, 3});
    TreeSet<int> s3({1, 2});
    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 == s3);
}

TEST(TreeSetTest, Inequality)
{
    TreeSet<int> s1({1, 2, 3});
    TreeSet<int> s2({1, 2});
    ASSERT_TRUE(s1 != s2);
}

TEST(TreeSetTest, IsBalanced)
{
    TreeSet<int> s({1, 2, 3});
    ASSERT_TRUE(s.is_balanced());
}
