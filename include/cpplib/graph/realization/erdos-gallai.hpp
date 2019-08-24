#pragma once
#include <cpplib/header>

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
    sort(dseq.rbegin(), dseq.rend());

    vi psum(dseq);
    for(int i=1; i<n; ++i)
        psum[i] += psum[i-1];

    if(psum[n - 1]%2)
        return false;

    vi minsum(n + 1, 0);
    for(int i=1; i<n; ++i){
        int x = upper_bound(dseq.rbegin(), dseq.rend(), i) - dseq.rbegin();
        // the quantity of degrees less or equal i.

        minsum[i] = i*max(i & 0, n - x - i) + psum[n - 1];
        // using (i & 0) to avoid the use of 0LL when using long long.

        int low = max(i-1, n-x-1);
        if(low >= 0)
            minsum[i] -= psum[low];
    }

    for(int k=1; k<=n; ++k){
        if(psum[k-1] > k*(k - 1) + minsum[k])
            return false;
    }
    return true;
}
