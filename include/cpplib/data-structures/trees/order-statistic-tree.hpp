#pragma once
#include <cpplib/header.hpp>

template<typename T>
using ost_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename K, typename V>
using ost_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
