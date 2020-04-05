#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Count Sort.
 *
 * Sorts a vector using a counting
 * approach.
 *
 * Note: It can only applied in vectors
 * which values are non-negative integers
 * up to MAX.
 *
 * Time Complexity: O(MAX + n).
 * Space Complexity: O(MAX).
 * Where n is the size of the vector.
 */
void count_sort(vi &v, const bool inc = true){
    int n = v.size(), cnt[MAX] = {};
    for(int i=0; i<n; ++i)
        cnt[v[i]]++;

    int k = (inc? 0 : v.size()-1);
    for(int i=0; i<MAX; ++i){
        for(int j=0; j<cnt[i]; ++j, k += (inc? 1 : -1))
            v[k] = i;
    }
}
