#include <gtest/gtest.h>
#include "Graph.cpp"


/// @brief: This build textbook Figure 20.4
Graph<char> getTextbookGraphDFS() {

    std::map<char, std::set<char>> adjList;
    adjList['u'] = { 'v', 'x' };
    adjList['v'] = { 'y' };
    adjList['x'] = { 'v' };
    adjList['y'] = { 'x' };
    adjList['w'] = { 'y', 'z' };
    adjList['z'] = { 'z' };

    Graph<char> g(adjList);
    return g;
}

template <typename T>
std::vector<int> getTimes(
    Graph<T> &g,
    const std::list<T> &order,
    std::function<int(GraphNode<T>)> getTime)
{
    std::vector<int> times;
    for (char vertex : order)
    {
        times.push_back(getTime(g[vertex]));
    }
    return times;
}

/// @brief Get the Discovery Times of each node in a graph given a order
/// @tparam T type of value stored in the graph
/// @param g a graph after DFS
/// @param order the order of nodes visited in DFS
/// @return a vector of discovery times
template <typename T>
std::vector<int> getDiscoveryTimes(Graph<T> &g, const std::list<T> &order)
{
    std::function<int(const GraphNode<T> &)> getDiscoveryTime = [](const GraphNode<T> &node) {
        return node.discovery_time;
    };
    return getTimes<T>(g, order, getDiscoveryTime);
}

/// @brief Get the Finish Times of each node in a graph given a order
/// @tparam T type of value stored in the graph
/// @param g a graph after DFS
/// @param order the order of nodes visited in DFS
/// @return a vector of finish times
template <typename T>
std::vector<int> getFinishTimes(Graph<T> &g, const std::list<T> &order)
{
    std::function<int(const GraphNode<T> &)> getFinishTime = [](const GraphNode<T> &node) {
        return node.finish_time;
    };
    return getTimes<T>(g, order, getFinishTime);
}

TEST(DFSTest, TextbookExampleTopologicalSort)
{
    Graph<char> g = getTextbookGraphDFS();
    std::list<char> dfs = g.DFS();
    std::list<char> expected{ 'w', 'z', 'u', 'v', 'y', 'x'};
    ASSERT_EQ(dfs.size(), g.size());
    ASSERT_EQ(dfs, expected);
}

TEST(DFSTest, TextbookExampleDiscoveryTimes)
{
    Graph<char> g = getTextbookGraphDFS();
    std::list<char> dfs = g.DFS();
    std::vector<int> discoveryTimes = getDiscoveryTimes(g, dfs);
    std::vector<int> expectedDiscoveryTimes{ 9, 10, 1, 2, 3, 4 };
    ASSERT_EQ(discoveryTimes, expectedDiscoveryTimes);
}
