#pragma once
#include <cpplib/header.hpp>

/**
 * Count Sort.
 *
 * Sorts a vector using a counting
 * approach.
 *
 * It can only applied in vectors
 * which integers are non-negative
 * up to MAX.
 *
 * Time Complexity: O(MAX+n).
 * Where n is the size of the graph.
 */
void count_sort(vi &v, bool inc = true){
    int n = v.size(), cnt[MAX] = {};
    for(int i=0; i<n; ++i)
        cnt[v[i]]++;

    int k = (inc? 0 : v.size()-1);
    for(int i=0; i<MAX; ++i){
        for(int j=0; j<cnt[i]; ++j, k += (inc? 1 : -1))
            v[k] = i;
    }
}

// TODO Radix Sort.
