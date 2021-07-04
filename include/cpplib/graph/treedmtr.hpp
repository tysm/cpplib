#pragma once
#include <cpplib/stdinc.hpp>

inline static tuple<int, int> bfs(vector<vector<int> > &adj, int s)
{
    queue<tuple<int, int, int> > q;
    q.emplace(0, s, -1);
    int res = -1, d = -1;
    while(!q.empty()) {
        int cur, u, p;
        tie(cur, u, p) = q.front();
        q.pop();
        if(cur > d) {
            res = u;
            d = cur;
        }
        for(int v: adj[u]) {
            if(v == p)
                continue;
            q.emplace(d + 1, v, u);
        }
    }
    return {res, d};
}

tuple<int, int, int> tree_diameter(vector<vector<int> > &adj)
{
    int ini = get<0>(bfs(adj, 0)), end, dis;
    tie(end, dis) = bfs(adj, ini);
    return {ini, end, dis};
}
