#pragma once
#include <cpplib/stdinc.hpp>

template<typename T>
using max_heap = priority_queue<T>;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T> >;
