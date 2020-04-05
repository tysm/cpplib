#pragma once
#include <cpplib/stdinc.hpp>

////
/// An order statistic tree is a BST with
/// the following additional operations:
/// - find_by_order(i): Finds the i-th
/// smallest element stored in the tree.
/// - order_of_key(key): Finds the index of
/// key in the sorted list of elements.
////

template<typename T>
using ost_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename K, typename V>
using ost_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
