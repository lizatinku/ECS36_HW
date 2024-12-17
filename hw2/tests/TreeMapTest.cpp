#include <gtest/gtest.h>
#include "TreeMap.cpp"

// Constructor (TreeMap()) test case
TEST(TreeMapTest, InstantiateEmptyMap)
{
    TreeMap<int, int> map;
    ASSERT_EQ(map.size(), 0);
}

// Constructor with Items case
TEST(TreeMapTest, InstantiateWithItems)
{
    std::vector<std::pair<int, int>> items = {{1, 100}, {2, 200}, {3, 300}};
    TreeMap<int, int> map(items);

    ASSERT_EQ(map.size(), 3);
    ASSERT_EQ(map.get(1), std::optional<int>(100));
    ASSERT_EQ(map.get(2), std::optional<int>(200));
    ASSERT_EQ(map.get(3), std::optional<int>(300));
}

// size case 1
TEST(TreeMapTest, InsertAndRetrieve)
{
    TreeMap<int, int> map;
    map.insert(1, 100);
    map.insert(2, 200);
    map.insert(3, 300);

    ASSERT_EQ(map.size(), 3);
    ASSERT_EQ(map.get(1), std::optional<int>(100));
    ASSERT_EQ(map.get(2), std::optional<int>(200));
    ASSERT_EQ(map.get(3), std::optional<int>(300));
}

// size case 2
TEST(TreeMapTest, UpdateExistingKey)
{
    TreeMap<int, int> map;
    map.insert(1, 100);
    map.insert(1, 200);

    ASSERT_EQ(map.size(), 1);
    ASSERT_EQ(map.get(1), std::optional<int>(200));
}

// size case 3
TEST(TreeMapTest, ContainsKey)
{
    TreeMap<int, int> map;
    map.insert(1, 100);

    ASSERT_TRUE(map.contains(1));
    ASSERT_FALSE(map.contains(2));
}

TEST(TreeMapTest, ClearMap)
{
    TreeMap<int, int> map;
    map.insert(1, 100);
    map.insert(2, 200);

    map.clear();
    ASSERT_EQ(map.size(), 0);
    ASSERT_FALSE(map.contains(1));
    ASSERT_FALSE(map.contains(2));
}

TEST(TreeMapTest, ToVector)
{
    TreeMap<int, int> map;
    map.insert(2, 200);
    map.insert(1, 100);
    map.insert(3, 300);

    std::vector<std::pair<int, int>> expected = {{1, 100}, {2, 200}, {3, 300}};
    ASSERT_EQ(map.to_vector(), expected);
}

TEST(TreeMapTest, IsEmpty)
{
    TreeMap<int, int> map;
    ASSERT_TRUE(map.is_empty());

    map.insert(1, 100);
    ASSERT_FALSE(map.is_empty());
}

TEST(TreeMapTest, Clear)
{
    TreeMap<int, int> map;
    map.insert(1, 100);
    map.insert(2, 200);

    ASSERT_FALSE(map.is_empty());
    ASSERT_EQ(map.size(), 2);

    map.clear();

    ASSERT_TRUE(map.is_empty());
    ASSERT_EQ(map.size(), 0);
    ASSERT_FALSE(map.contains(1));
    ASSERT_FALSE(map.contains(2));
}