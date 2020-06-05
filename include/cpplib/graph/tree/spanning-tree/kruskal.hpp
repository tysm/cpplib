#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/data-structure/union-find.hpp>

/**
 * Kruskal.
 *
 * Computes the minimum spanning tree.
 *
 * Time Complexity: O(m*log(n)).
 * Space Complexity: O(n+m).
 * Where n is the size of the graph and m is the number of edges.
 */
vector<pair<int, ii> > kruskal(const int n, vector<pair<int, ii> > edges){
    vector<pair<int, ii> > res;
    UnionFind dsu(n);
    sort(all(edges));
    for(pair<int, ii> &e : edges){
        if(dsu.merge(e.ss.ff, e.ss.ss))
            res.pb(e);
    }
    return res;
}
