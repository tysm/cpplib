#pragma once
#include <cpplib/header.hpp>
#include <cpplib/utility/count-sort.hpp>

/**
 * Erdos Gallai.
 *
 * Provides a graph realization check,
 * based on its vertices degrees.
 *
 * Time Complexity: O(n).
 * Where n is the size of the graph.
 */
bool erdos(vi dseq){
    // dseq = degree sequence.
    int n = dseq.size();

    count_sort(dseq, false);
    if(dseq[0] >= n)
        return false;
    // if it's not possible to use count-sort
    // use the O(n*log(n)) sort:
    // sort(dseq.rbegin(), dseq.rend());

    vi psum(dseq);
    for(int i=1; i<n; ++i)
        psum[i] += psum[i-1];
    if(psum[n-1]%2)
        return false;

    for(int k=1, i=n-1; k<=n; ++k){
        while(i>=0 and dseq[i] < k)
            i--;

        int minsumk = k*max(k & 0, i+1-k) + (psum[n-1] - psum[max(k-1, i)]);
        // using (k & 0) to avoid the use of
        // 0LL when using long long.

        if(psum[k-1] > k*(k-1) + minsumk)
            return false;
    }
    return true;
}
