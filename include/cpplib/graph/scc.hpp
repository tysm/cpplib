#pragma once
#include <cpplib/stdinc.hpp>

inline void dfs(const vector<vector<int> > &adj, vector<bool> &vis, vector<int> &order, const int u)
{
    vis[u] = true;
    for(int v: adj[u]) {
        if(vis[v])
            continue;
        dfs(adj, vis, order, v);
    }
    order.emplace_back(u);
}

tuple<vector<vector<int> >, vector<int> > scc(const vector<vector<int> > &adj)
{
    int n = adj.size();
    assert(n > 0);
    vector<vector<int> > iadj(n);
    for(int i = 0; i < n; ++i) {
        for(int j: adj[i])
            iadj[j].eb(i);
    }

    vector<int> order;

    vector<bool> vis(n);
    for(int i = 0; i < n; ++i) {
        if(!vis[i])
            dfs(adj, vis, order, i);
    }
    reverse(all(order));

    int k = 0;
    vector<int> repr(n, -1);
    queue<int> q;
    for(int i: order) {
        if(repr[i] != -1)
            continue;

        q.emplace(i);
        repr[i] = k;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int v: iadj[u]) {
                if(repr[v] != -1)
                    continue;
                q.emplace(v);
                repr[v] = k;
            }
        }
        k++;
    }

    vector<vector<int> > res(k);
    for(int i = 0; i < n; ++i) {
        for(int j: adj[i]) {
            int u = repr[i], v = repr[j];
            if(u == v)
                continue;
            res[u].eb(v);
        }
    }
    return {res, repr};
}
