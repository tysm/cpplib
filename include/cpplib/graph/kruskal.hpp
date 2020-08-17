#pragma once
#include <cpplib/adt/dsu.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Kruskal.
 *
 * Computes the minimum spanning tree.
 *
 * Time Complexity: O(m*log(n)).
 * Space Complexity: O(n+m).
 * Where n is the size of the graph and m is the number of edges.
 */
vector<tuple<int, int, int> > kruskal(const int n, vector<tuple<int, int, int> > edges)
{
    sort(all(edges));
    DSU dsu(n);
    vector<tuple<int, int, int> > res;
    for(auto &e: edges) {
        int w, u, v;
        tie(w, u, v) = e;
        if(dsu.merge(u, v))
            res.emplace_back(e);
    }
    return res;
}
