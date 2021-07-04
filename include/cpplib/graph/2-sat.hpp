#pragma once
#include <cpplib/graph/scc.hpp>
#include <cpplib/stdinc.hpp>

vector<vector<int> > graph(const int n, const vector<pair<int, int> > &disj)
{
    vector<vector<int> > adj(2 * n);
    for(pair<int, int> d: disj) {
        adj[d.first ^ 1].eb(d.second);
        adj[d.second ^ 1].eb(d.first);
    }
    return adj;
}

inline bool check(const vector<vector<int> > &adj)
{
    vector<vector<int> > comps;
    vector<int> repr;
    tie(comps, repr) = scc(adj);

    int n = adj.size();
    for(int i = 0; i < n; i += 2) {
        int u = repr[i], v = repr[i + 1];
        if(u == v)
            return false;
    }
    return true;
}

inline bool check(const int n, const vector<pair<int, int> > &disj)
{
    return check(graph(n, disj));
}

inline vector<bool> solve(const vector<vector<int> > &adj)
{
    int n = adj.size();
    vector<vector<int> > comps;
    vector<int> repr;
    tie(comps, repr) = scc(adj);

    vector<bool> res(n / 2);
    for(int i = 0; i < n; i += 2) {
        if(repr[i] == repr[i + 1])
            return vector<bool>();
        res[i / 2] = (repr[i] > repr[i + 1]);
    }
    return res;
}

inline vector<bool> solve(const int n, const vector<pair<int, int> > &disj)
{
    return solve(graph(n, disj));
}
