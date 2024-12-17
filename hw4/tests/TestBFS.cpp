
#include <gtest/gtest.h>
#include "Graph.cpp"

using namespace std;

Graph<char> getTextbookGraphBFS() {

    std::map<char, std::set<char>> adjList;
    adjList['w'] = { 'r', 'v', 'x', 'z' };
    adjList['r'] = { 'w', 't', 's' };
    adjList['t'] = { 'r', 'u' };
    adjList['u'] = { 't', 's', 'y' };
    adjList['s'] = { 'r', 'u', 'v' };
    adjList['v'] = { 'w', 's', 'y' };
    adjList['x'] = { 'w', 'y', 'z' };
    adjList['y'] = { 'x', 'u', 'v' };
    adjList['z'] = { 'w', 'x' };

    Graph<char> g(adjList);
    return g;
}

TEST(BFSTest, InstantiateGraphFromEdges)
{
    Graph<int> g({ {1, 2}, {1, 3}, {2, 3} });
    ASSERT_EQ(g.size(), 3);

    std::vector<int> bfs = g.BFS(1);
    std::vector<int> expected{ 1, 2, 3 };

    ASSERT_EQ(bfs.size(), g.size());
    ASSERT_EQ(bfs, expected);
}