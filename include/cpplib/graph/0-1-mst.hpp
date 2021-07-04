#pragma once
#include <cpplib/adt/dsu.hpp>
#include <cpplib/stdinc.hpp>

///
// Given an undirected weighted n-complete graph such that the weight of each
// edge is either 0 or 1 and all 1 edges are given (all m edges of weight 1 in
// total), find:
// - the weight of the minimum spanning tree (the size of the resulting dsu);
// - the minimum spanning tree...
//
// Given an undirected weighted graph such that all nodes are connected
// except m given pairs.
// - compute the connected components (the resulting dsu)...
///
DSU solve(const vector<vector<int> > &adj1)
{
    int n = adj1.size();
    DSU dsu(n);

    set<int> keys;
    map<int, int> cnt;
    for(int v = 0; v < n; ++v) {
        for(int u: adj1[v]) {
            if(u > v)
                continue;
            int k = dsu.find(u);
            keys.emplace(k);
            cnt[k]++;
        }
        vector<int> rem;
        for(int u: keys) {
            int &c = cnt[u];
            if(c < dsu.size(u)) {
                dsu.merge(u, v);
                rem.emplace_back(u);
            }
            c = 0;
        }
        for(int u: rem) {
            keys.erase(u);
            cnt.erase(u);
        }
        int k = dsu.find(v);
        keys.emplace(k);
        cnt[k] = 0;
    }
    return dsu;
}
