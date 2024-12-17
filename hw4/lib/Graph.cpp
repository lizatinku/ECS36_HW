#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "Graph.hpp"
#include "GraphNode.hpp"
#include <queue>
#include <optional>

template <typename T>
void Graph<T>::DFS_visit(const T &u, int &time, std::list<T> &record)
{
    GraphNode<T> &node = _vertices[u];
    node.color = Gray;
    node.discovery_time = ++time;

    for (const T &v : _adjList[u])
    {
        GraphNode<T> &neighbor = _vertices[v];
        if (neighbor.color == White)
        {
            neighbor.predecessor = u;
            DFS_visit(v, time, record);
        }
    }

    node.color = Black;
    node.finish_time = ++time;

    record.push_front(u);
}

template <typename T>
Graph<T>::Graph(const std::vector<std::pair<T, T>> &edges)
{
    for (const auto &edge : edges)
    {
        const T &from = edge.first;
        const T &to = edge.second;

        _adjList[from].insert(to);
        if (_adjList.find(to) == _adjList.end())
        {
            _adjList[to];
        }

        if (_vertices.find(from) == _vertices.end())
        {
            _vertices[from] = GraphNode<T>(from);
        }
        if (_vertices.find(to) == _vertices.end())
        {
            _vertices[to] = GraphNode<T>(to);
        }
    }
}

template <typename T>
Graph<T>::Graph(const std::map<T, std::set<T>> &adjList)
{
    _adjList = adjList;

    for (const auto &entry : adjList)
    {
        const T &vertex = entry.first;
        if (_vertices.find(vertex) == _vertices.end())
        {
            _vertices[vertex] = GraphNode<T>(vertex);
        }
        for (const T &neighbor : entry.second)
        {
            if (_vertices.find(neighbor) == _vertices.end())
            {
                _vertices[neighbor] = GraphNode<T>(neighbor);
            }
        }
    }
}

template <typename T>
int Graph<T>::size() const
{
    return _vertices.size();
}

template <typename T>
void Graph<T>::addVertex(T vertex)
{
    if (_vertices.find(vertex) == _vertices.end())
    {
        _vertices[vertex] = GraphNode<T>(vertex);
    }
    if (_adjList.find(vertex) == _adjList.end())
    {
        _adjList[vertex] = std::set<T>();
    }
}

template <typename T>
void Graph<T>::addEdge(T from, T to)
{
    addVertex(from);
    addVertex(to);

    _adjList[from].insert(to);
}

template <typename T>
bool Graph<T>::hasEdge(T from, T to) const
{
    auto it = _adjList.find(from);
    if (it != _adjList.end())
    {
        const auto &neighbors = it->second;
        return neighbors.find(to) != neighbors.end();
    }
    return false;
}

template <typename T>
std::optional<std::set<T>> Graph<T>::getNeighbors(T vertex) const
{
    auto it = _adjList.find(vertex);
    if (it != _adjList.end())
    {
        return it->second;
    }
    return std::nullopt;
}

template <typename T>
std::list<T> Graph<T>::DFS()
{
    for (auto &pair : _vertices)
    {
        pair.second.color = White;
        pair.second.predecessor = std::nullopt;
        pair.second.discovery_time = -1;
        pair.second.finish_time = -1;
    }

    std::list<T> record;
    int time = 0;

    for (const auto &pair : _vertices)
    {
        const T &vertex = pair.first;
        if (_vertices[vertex].color == White)
        {
            DFS_visit(vertex, time, record);
        }
    }

    return record;
}

template <typename T>
std::vector<T> Graph<T>::BFS(T start)
{
    std::vector<T> traversalOrder;

    if (_vertices.find(start) == _vertices.end())
    {
        return traversalOrder;
    }

    for (auto &pair : _vertices)
    {
        pair.second.color = White;
        pair.second.distance = -1;
        pair.second.predecessor = std::nullopt;
    }

    _vertices[start].color = Gray;
    _vertices[start].distance = 0;
    std::queue<T> q;
    q.push(start);

    while (!q.empty())
    {
        T current = q.front();
        q.pop();
        traversalOrder.push_back(current);

        for (const T &neighbor : _adjList[current])
        {
            if (_vertices[neighbor].color == White)
            {
                _vertices[neighbor].color = Gray;
                _vertices[neighbor].distance = _vertices[current].distance + 1;
                _vertices[neighbor].predecessor = current;
                q.push(neighbor);
            }
        }

        _vertices[current].color = Black;
    }

    return traversalOrder;
}

template <typename T>
int Graph<T>::shortestPath(T start, T end)
{
    if (_vertices.find(start) == _vertices.end() || _vertices.find(end) == _vertices.end())
    {
        return -1;
    }

    for (auto &pair : _vertices)
    {
        pair.second.color = White;
        pair.second.distance = -1;
        pair.second.predecessor = std::nullopt;
    }

    _vertices[start].color = Gray;
    _vertices[start].distance = 0;
    std::queue<T> q;
    q.push(start);

    while (!q.empty())
    {
        T current = q.front();
        q.pop();

        if (current == end)
        {
            return _vertices[current].distance;
        }

        for (const T &neighbor : _adjList[current])
        {
            if (_vertices[neighbor].color == White)
            {
                _vertices[neighbor].color = Gray;
                _vertices[neighbor].distance = _vertices[current].distance + 1;
                _vertices[neighbor].predecessor = current;
                q.push(neighbor);
            }
        }

        _vertices[current].color = Black;
    }

    return -1;
}

#endif // GRAPH_CPP