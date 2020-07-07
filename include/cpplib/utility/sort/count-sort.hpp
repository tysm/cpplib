#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Count Sort.
 *
 * Sorts a vector using a counting
 * approach.
 *
 * Note: It can only applied in vectors
 * which values are non-negative integers.
 *
 * Time Complexity: O(n + m).
 * Space Complexity: O(m).
 * Where n is the vector size and m is the greatest integer in the vector.
 */
template<typename T,
typename enable_if<is_integral<T>::value, uint>::type = 0>
void count_sort(vector<T> &v, const bool non_decreasing = true){
    uint n = v.size(), m = *max_element(v.begin(), v.end());
    vector<uint> cnt(m+1);
    for(uint i : v){
        assert((T)i >= 0);
        cnt[i]++;
    }
    for(uint i = 0, j = (non_decreasing? 0 : n-1); i <= m; ++i){
        for(; cnt[i] > 0; --cnt[i], j += (non_decreasing? 1 : -1))
            v[j] = i;
    }
}
