#include <gtest/gtest.h>
#include "Graph.cpp"

TEST(GraphTest, InstantiateEmptyGraph)
{
    Graph<int> g;
    ASSERT_EQ(g.size(), 0);
}

TEST(GraphTest, InstantiateFromVector)
{
    std::vector<std::pair<int, int>> edges({{1, 2}, {1, 3}, {2, 3}});
    Graph<int> g(edges);
    ASSERT_EQ(g.size(), 3);
    ASSERT_TRUE(g.hasEdge(1, 2));
}

TEST(GraphTest, AddVertex)
{
    Graph<char> g;
    g.addVertex('a');

    ASSERT_EQ(g.size(), 1);
    ASSERT_FALSE(g.hasEdge('a', 'b'));
    ASSERT_EQ(g.getNeighbors('a').value().size(), 0);
}

TEST(GraphTest, DFSVisit)
{
    std::vector<std::pair<int, int>> edges = {
        {1, 2}, {1, 3}, {2, 4}, {3, 4}};
    Graph<int> g(edges);

    std::list<int> topologicalOrder = g.DFS();

    // Expected topological order: 1 -> 3 -> 2 -> 4 or 1 -> 2 -> 3 -> 4
    std::vector<int> validOrder1 = {1, 2, 3, 4};
    std::vector<int> validOrder2 = {1, 3, 2, 4};
    ASSERT_TRUE(std::equal(topologicalOrder.begin(), topologicalOrder.end(), validOrder1.begin()) ||
                std::equal(topologicalOrder.begin(), topologicalOrder.end(), validOrder2.begin()));

    ASSERT_EQ(g[1].discovery_time, 1);
    ASSERT_GT(g[1].finish_time, g[2].finish_time);       // Ensure 1 finishes after its neighbors
    ASSERT_GT(g[2].discovery_time, g[1].discovery_time); // Ensure neighbors are discovered later
    ASSERT_EQ(g[4].color, Black);                        // Ensure all nodes are visited
}

TEST(GraphTest, GraphFromVectorOfEdges)
{
    std::vector<std::pair<int, int>> edges = {
        {1, 2}, {1, 3}, {2, 4}, {3, 4}, {4, 5}};
    Graph<int> g(edges);

    ASSERT_EQ(g.size(), 5);

    ASSERT_TRUE(g.hasEdge(1, 2));
    ASSERT_TRUE(g.hasEdge(1, 3));
    ASSERT_TRUE(g.hasEdge(2, 4));
    ASSERT_TRUE(g.hasEdge(3, 4));
    ASSERT_TRUE(g.hasEdge(4, 5));

    ASSERT_FALSE(g.hasEdge(2, 5));
    ASSERT_FALSE(g.hasEdge(5, 1));

    ASSERT_EQ(g.getNeighbors(1).value(), std::set<int>({2, 3}));
    ASSERT_EQ(g.getNeighbors(4).value(), std::set<int>({5}));
    ASSERT_EQ(g.getNeighbors(5).value().size(), 0);

    for (int i = 1; i <= 5; ++i)
    {
        ASSERT_NO_THROW(g[i]);
    }
}

TEST(GraphTest, AddEdge)
{
    // Create an empty graph
    Graph<int> g;

    // Add an edge between two vertices
    g.addEdge(1, 2);

    // Check if the vertices exist
    ASSERT_EQ(g.size(), 2); // Both vertices should be added automatically
    ASSERT_TRUE(g.getNeighbors(1).has_value());
    ASSERT_TRUE(g.getNeighbors(2).has_value());

    // Check adjacency list
    ASSERT_EQ(g.getNeighbors(1).value(), std::set<int>({2})); // 1 -> 2
    ASSERT_EQ(g.getNeighbors(2).value().size(), 0);           // 2 has no outgoing edges

    // Add another edge
    g.addEdge(2, 3);

    // Check if the new vertex exists
    ASSERT_EQ(g.size(), 3);

    // Check adjacency list again
    ASSERT_EQ(g.getNeighbors(2).value(), std::set<int>({3})); // 2 -> 3
    ASSERT_EQ(g.getNeighbors(3).value().size(), 0);           // 3 has no outgoing edges

    // Add an edge that already exists (should not duplicate)
    g.addEdge(1, 2);

    // Ensure no duplicate edges are created
    ASSERT_EQ(g.getNeighbors(1).value().size(), 1);
    ASSERT_EQ(g.getNeighbors(1).value(), std::set<int>({2}));
}

TEST(GraphTest, HasEdge)
{
    // Create a graph with some edges
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    // Check for existing edges
    ASSERT_TRUE(g.hasEdge(1, 2)); // 1 -> 2 exists
    ASSERT_TRUE(g.hasEdge(2, 3)); // 2 -> 3 exists
    ASSERT_TRUE(g.hasEdge(3, 4)); // 3 -> 4 exists

    // Check for non-existent edges
    ASSERT_FALSE(g.hasEdge(1, 3)); // No direct edge from 1 -> 3
    ASSERT_FALSE(g.hasEdge(2, 4)); // No direct edge from 2 -> 4
    ASSERT_FALSE(g.hasEdge(4, 1)); // No edge from 4 -> 1

    // Check for edges from or to vertices that don’t exist
    ASSERT_FALSE(g.hasEdge(5, 1)); // Vertex 5 doesn't exist
    ASSERT_FALSE(g.hasEdge(1, 5)); // Vertex 5 doesn't exist
}

TEST(GraphTest, GetNeighbors)
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    auto neighbors1 = g.getNeighbors(1);
    ASSERT_TRUE(neighbors1.has_value());
    ASSERT_EQ(neighbors1.value(), std::set<int>({2, 3}));

    auto neighbors2 = g.getNeighbors(2);
    ASSERT_TRUE(neighbors2.has_value());
    ASSERT_EQ(neighbors2.value(), std::set<int>({4}));

    auto neighbors3 = g.getNeighbors(3);
    ASSERT_TRUE(neighbors3.has_value());
    ASSERT_EQ(neighbors3.value().size(), 0);

    g.addVertex(5);
    auto neighbors5 = g.getNeighbors(5);
    ASSERT_TRUE(neighbors5.has_value());
    ASSERT_EQ(neighbors5.value().size(), 0);

    auto neighbors6 = g.getNeighbors(6);
    ASSERT_FALSE(neighbors6.has_value());
}
