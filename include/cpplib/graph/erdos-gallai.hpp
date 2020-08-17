#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/utility/sort.hpp>

/**
 * Erdos Gallai.
 *
 * Provides a graph realization check given
 * its vertices degrees.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the graph.
 */
bool erdos(vector<int> degrees)
{
    int n = degrees.size();

    if(*max_element(degrees.begin(), degrees.end()) >= n)
        return false;
    count_sort(degrees, false);

    vector<int> psum(degrees);
    for(int i = 1; i < n; ++i)
        psum[i] += psum[i - 1];
    if(psum[n - 1] & 1)
        return false;

    for(int k = 1, i = n - 1; k <= n; ++k) {
        while(i >= 0 and degrees[i] < k)
            i--;

        int min_sum_k = k * max(i + 1 - k, (int)0) + (psum[n - 1] - psum[max(k - 1, i)]);
        if(psum[k - 1] > k * (k - 1) + min_sum_k)
            return false;
    }
    return true;
}
