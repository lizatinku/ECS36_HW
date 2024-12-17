#ifndef TREE_SET_CPP
#define TREE_SET_CPP

#include "TreeSet.hpp"
#include "BinaryTreeNode.hpp"
#include <optional>
#include <vector>
#include <functional>

// Constructor
template <typename T>
TreeSet<T>::TreeSet() : _root(nullptr), _size(0)
{
    _comparator = [](T left, T right)
    {
        if (left < right)
            return -1;
        else if (left > right)
            return 1;
        return 0;
    };
}

// Constructor with a comparator function
template <typename T>
TreeSet<T>::TreeSet(std::function<int(T, T)> comparator) : _root(nullptr), _size(0), _comparator(comparator) {}

// Constructor with a vector of items
template <typename T>
TreeSet<T>::TreeSet(const std::vector<T> &items) : _root(nullptr), _size(0)
{
    _comparator = [](T left, T right)
    {
        if (left < right)
            return -1;
        else if (left > right)
            return 1;
        return 0;
    };

    for (const T &item : items)
    {
        add(item);
    }
}

// Constructor with both a vector of items and a comparator function
template <typename T>
TreeSet<T>::TreeSet(const std::vector<T> &items, std::function<int(T, T)> comparator)
    : _root(nullptr), _size(0), _comparator(comparator)
{

    for (const T &item : items)
    {
        add(item);
    }
}

// size() - Returns the number of elements in the tree
template <typename T>
size_t TreeSet<T>::size() const
{
    return _size;
}

// is_empty() - Checks if the set is empty
template <typename T>
bool TreeSet<T>::is_empty() const
{
    return _size == 0;
}

// add() - Adds a value to the tree, replacing the existing value if present
template <typename T>
void TreeSet<T>::add(T value)
{
    BinaryTreeNode<T> *newNode = new BinaryTreeNode<T>(value);
    newNode->_left = newNode->_right = nullptr;
    newNode->_color = Color::Red;

    if (_root == nullptr)
    {
        _root = newNode;
        _root->_color = Color::Black;
    }
    else
    {
        BinaryTreeNode<T> *current = _root;
        BinaryTreeNode<T> *parent = nullptr;

        while (current != nullptr)
        {
            parent = current;
            int comparison = _comparator(value, current->value);
            if (comparison == 0)
            {
                current->value = value;
                delete newNode;
                return;
            }
            else if (comparison < 0)
            {
                current = current->_left;
            }
            else
            {
                current = current->_right;
            }
        }

        newNode->_parent = parent;
        if (_comparator(value, parent->value) < 0)
        {
            parent->_left = newNode;
        }
        else
        {
            parent->_right = newNode;
        }

        fix_violation(newNode);
    }

    _size++;
}

// contains() - Checks if a value exists in the set
template <typename T>
bool TreeSet<T>::contains(T value) const
{
    BinaryTreeNode<T> *current = _root;
    while (current != nullptr)
    {
        int comparison = _comparator(value, current->value);
        if (comparison == 0)
            return true;
        else if (comparison < 0)
            current = current->_left;
        else
            current = current->_right;
    }
    return false;
}

// min() - Finds the smallest value in the set
template <typename T>
std::optional<T> TreeSet<T>::min() const
{
    if (_root == nullptr)
        return std::nullopt;
    BinaryTreeNode<T> *current = _root;
    while (current->_left != nullptr)
        current = current->_left;
    return current->value;
}

// max() - Finds the largest value in the set
template <typename T>
std::optional<T> TreeSet<T>::max() const
{
    if (_root == nullptr)
        return std::nullopt;
    BinaryTreeNode<T> *current = _root;
    while (current->_right != nullptr)
        current = current->_right;
    return current->value;
}

template <typename T>
std::vector<T> TreeSet<T>::to_vector() const
{
    std::vector<T> result;

    // In-order traversal using a lambda to add elements to result
    std::function<void(BinaryTreeNode<T> *)> in_order = [&](BinaryTreeNode<T> *node)
    {
        if (node == nullptr)
            return;
        in_order(node->_left);
        result.push_back(node->value);
        in_order(node->_right);
    };

    in_order(_root);
    return result;
}

// get() - Finds and returns a value in the tree if present
template <typename T>
std::optional<T> TreeSet<T>::get(T value) const
{
    BinaryTreeNode<T> *current = _root;
    while (current != nullptr)
    {
        int comparison = _comparator(value, current->value);
        if (comparison == 0)
            return current->value;
        else if (comparison < 0)
            current = current->_left;
        else
            current = current->_right;
    }
    return std::nullopt;
}

template <typename T>
TreeSet<T> TreeSet<T>::operator+(const TreeSet &other)
{
    TreeSet<T> result;

    // Add all elements from the current set to result
    for (const T &value : this->to_vector())
    {
        result.add(value);
    }

    // Add all elements from the other set to result
    for (const T &value : other.to_vector())
    {
        result.add(value);
    }

    return result;
}

// operator+= - Adds all elements from other set to this set (in-place union)
template <typename T>
TreeSet<T> &TreeSet<T>::operator+=(const TreeSet &other)
{
    for (const T &value : other.to_vector())
    {
        this->add(value);
    }
    return *this;
}

// operator& - Returns a new set containing the intersection of this set and other
template <typename T>
TreeSet<T> TreeSet<T>::operator&(const TreeSet &other)
{
    TreeSet<T> result;

    for (const T &value : this->to_vector())
    {
        if (other.contains(value))
        {
            result.add(value);
        }
    }

    return result;
}

// operator== - Checks if two sets contain the same elements
template <typename T>
bool TreeSet<T>::operator==(const TreeSet &other) const
{
    // If sizes are different, sets are not equal
    if (this->size() != other.size())
    {
        return false;
    }

    // Check if all elements in this set are contained in the other set
    for (const T &value : this->to_vector())
    {
        if (!other.contains(value))
        {
            return false;
        }
    }

    return true;
}

// operator!= - Checks if two sets contain different elements
template <typename T>
bool TreeSet<T>::operator!=(const TreeSet &other) const
{
    // Use the equality operator and return its negation
    return !(*this == other);
}

// clear() - Removes every element in the set
template <typename T>
void TreeSet<T>::clear()
{
    std::function<void(BinaryTreeNode<T> *)> delete_subtree = [&](BinaryTreeNode<T> *node)
    {
        if (node == nullptr)
            return;
        delete_subtree(node->_left);  // Recursively delete left subtree
        delete_subtree(node->_right); // Recursively delete right subtree
        delete node;                  // Delete current node
    };

    delete_subtree(_root); // Start deleting from the root
    _root = nullptr;       // Set root to nullptr after all nodes are deleted
    _size = 0;             // Reset size
}

template <typename T>
TreeSet<T>::~TreeSet()
{
    clear();
}

template <typename T>
void TreeSet<T>::rotate_left(BinaryTreeNode<T> *x)
{
    BinaryTreeNode<T> *y = x->_right;
    x->_right = y->_left;

    if (y->_left != nullptr)
    {
        y->_left->_parent = x;
    }

    y->_parent = x->_parent;

    if (x->_parent == nullptr)
    {
        _root = y;
    }
    else if (x == x->_parent->_left)
    {
        x->_parent->_left = y;
    }
    else
    {
        x->_parent->_right = y;
    }

    y->_left = x;
    x->_parent = y;
}

template <typename T>
void TreeSet<T>::rotate_right(BinaryTreeNode<T> *y)
{
    BinaryTreeNode<T> *x = y->_left;
    y->_left = x->_right;

    if (x->_right != nullptr)
    {
        x->_right->_parent = y;
    }

    x->_parent = y->_parent;

    if (y->_parent == nullptr)
    {
        _root = x;
    }
    else if (y == y->_parent->_right)
    {
        y->_parent->_right = x;
    }
    else
    {
        y->_parent->_left = x;
    }

    x->_right = y;
    y->_parent = x;
}

template <typename T>
void TreeSet<T>::fix_violation(BinaryTreeNode<T> *z)
{
    while (z != _root && z->_parent->_color == Red)
    {
        if (z->_parent == z->_parent->_parent->_left)
        {
            BinaryTreeNode<T> *y = z->_parent->_parent->_right; // z's uncle
            if (y && y->_color == Red)
            { // Case 1
                z->_parent->_color = Black;
                y->_color = Black;
                z->_parent->_parent->_color = Red;
                z = z->_parent->_parent;
            }
            else
            {
                if (z == z->_parent->_right)
                { // Case 2
                    z = z->_parent;
                    rotate_left(z);
                }
                z->_parent->_color = Black; // Case 3
                z->_parent->_parent->_color = Red;
                rotate_right(z->_parent->_parent);
            }
        }
        else
        {
            BinaryTreeNode<T> *y = z->_parent->_parent->_left; // Mirror image of above
            if (y && y->_color == Red)
            {
                z->_parent->_color = Black;
                y->_color = Black;
                z->_parent->_parent->_color = Red;
                z = z->_parent->_parent;
            }
            else
            {
                if (z == z->_parent->_left)
                {
                    z = z->_parent;
                    rotate_right(z);
                }
                z->_parent->_color = Black;
                z->_parent->_parent->_color = Red;
                rotate_left(z->_parent->_parent);
            }
        }
    }
    _root->_color = Black;
}

#endif
