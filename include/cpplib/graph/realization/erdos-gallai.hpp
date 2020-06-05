#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/utility/sort/count-sort.hpp>

/**
 * Erdos Gallai.
 *
 * Provides a graph realization check given
 * its vertices degrees.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(max(n, MAX)).
 * Where n is the size of the graph.
 */
bool erdos(vi dgrs){
    int n = dgrs.size();

    count_sort(dgrs, false);
    if(dgrs[0] >= n)
        return false;
    // if it's not possible to use count-sort
    // use the O(n*log(n)) sort:
    // sort(rall(dgrs));

    vi psum(dgrs);
    for(int i=1; i<n; ++i)
        psum[i] += psum[i-1];
    if(psum[n-1]%2)
        return false;

    for(int k=1, i=n-1; k<=n; ++k){
        while(i>=0 and dgrs[i] < k)
            i--;

        int minsumk = k*max(i+1-k, (int)0) + (psum[n-1] - psum[max(k-1, i)]);
        if(psum[k-1] > k*(k-1) + minsumk)
            return false;
    }
    return true;
}
