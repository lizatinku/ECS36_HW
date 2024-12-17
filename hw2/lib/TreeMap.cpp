#ifndef TREE_MAP_CPP
#define TREE_MAP_CPP

#include "TreeMap.hpp"
#include "TreeSet.cpp"
#include <optional>
#include <functional>

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap()
    : _tree([](const std::pair<TKey, TValue> &a, const std::pair<TKey, TValue> &b)
            {
        if (a.first < b.first) return -1;
        if (a.first > b.first) return 1;
        return 0; }) {}

// Constructor with a vector of items
template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::TreeMap(const std::vector<std::pair<TKey, TValue>> &items)
    : TreeMap()
{
    for (const auto &item : items)
    {
        _tree.add(item);
    }
}

template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::insert(TKey key, TValue value)
{
    _tree.add(std::make_pair(key, value));
}

template <typename TKey, typename TValue>
size_t TreeMap<TKey, TValue>::size() const
{
    return _tree.size();
}

template <typename TKey, typename TValue>
std::optional<TValue> TreeMap<TKey, TValue>::get(TKey key) const
{
    auto search_pair = std::make_pair(key, TValue{});

    auto result = _tree.get(search_pair);

    if (result)
    {
        return result->second;
    }
    else
    {
        return std::nullopt;
    }
}

template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::contains(TKey key) const
{
    auto search_pair = std::make_pair(key, TValue{});
    auto result = _tree.get(search_pair);
    return result.has_value();
}

template <typename TKey, typename TValue>
std::vector<std::pair<TKey, TValue>> TreeMap<TKey, TValue>::to_vector() const
{
    std::vector<std::pair<TKey, TValue>> elements = _tree.to_vector();
    return elements;
}

template <typename TKey, typename TValue>
bool TreeMap<TKey, TValue>::is_empty() const
{
    return _tree.size() == 0;
}

template <typename TKey, typename TValue>
void TreeMap<TKey, TValue>::clear()
{
    _tree.clear();
}

template <typename TKey, typename TValue>
TreeMap<TKey, TValue>::~TreeMap()
{
    clear();
}

#endif
