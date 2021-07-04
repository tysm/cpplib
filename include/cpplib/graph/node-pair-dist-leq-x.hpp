#pragma once
#include <cpplib/adt/segtree.hpp>
#include <cpplib/stdinc.hpp>

// Based on 2018 Arab Collegiate Programming Contest (ACPC 2018)
// problem A, using DSU on tree.

// compute the size of each.
static void dfs(const vector<vector<int> > &adj, vector<int> &cnt, const int u, const int p)
{
    cnt[u] = 1;
    for(int v: adj[u]) {
        if(v == p)
            continue;
        dfs(adj, cnt, v, u);
        cnt[u] += cnt[v];
    }
}

// query the number of nodes whose depth <= x.
static int query(SegTree<RSumQ, int> &st, const int x, const int n)
{
    if(x >= 0)
        return st.query(0, min(x, n - 1));
    return 0;
}

// update the depth segtree (adding or removing).
static void update_st(const vector<vector<int> > &adj, const int u, const int p, SegTree<RSumQ, int> &st, const int pos, const int delta)
{
    st.update(pos, delta);
    for(int v: adj[u]) {
        if(v == p)
            continue;
        update_st(adj, v, u, st, pos + 1, delta);
    }
}

// compute the answer on a light subtree.
static int compute(const vector<vector<int> > &adj, const int u, const int p, SegTree<RSumQ, int> &st, const int bd, const int d, const int x)
{
    int res = query(st, x - d + 2 * bd, adj.size());
    for(int v: adj[u]) {
        if(v == p)
            continue;
        res += compute(adj, v, u, st, bd, d + 1, x);
    }
    return res;
}

// compute the answer on a subtree by putting it as base.
static int base_at(const vector<vector<int> > &adj, const vector<int> &cnt, queue<pair<int, int> > &light, const int u, const int p, SegTree<RSumQ, int> &st, const int d, const int x)
{
    int h = -1;
    for(int v: adj[u]) {
        if(v == p)
            continue;
        if(h == -1 or cnt[v] > cnt[h])  // v is the new heavy.
            h = v;
    }

    int res = 0;
    if(h != -1)
        res += base_at(adj, cnt, light, h, u, st, d + 1, x);  // solve the heavy and add it to st.

    // now u is the base and h (the heavy) is already in the st.
    for(int v: adj[u]) {
        if(v == p or v == h)
            continue;
        res += compute(adj, v, u, st, d, d + 1, x);  // compute ans between light and heavy,

        update_st(adj, v, u, st, d + 1, 1);  // add light to st (so we can compute between light and light in st).

        light.ep(v, u);  // add light subtree to compute later.
    }

    // now everyone (except u) in this subtree is in the st,
    // now we need to compute the as for our base.
    res += query(st, x + d, adj.size());

    st.update(d, 1);  // add current to st.
    return res;
}

// compute the number of distinct vertices of a tree such that their distance <= x.
// O(n*exp(log(n), 2)).
int solve(const vector<vector<int> > &adj, const int x)
{
    int n = adj.size();
    if(x <= 0)
        return 0;

    vector<int> cnt(n);
    dfs(adj, cnt, 0, -1);

    queue<pair<int, int> > light;
    light.ep(0, -1);

    SegTree<RSumQ, int> st(n);

    int res = 0;
    while(!light.empty()) {
        int u = light.front().ff, p = light.front().ss;
        light.pop();

        res += base_at(adj, cnt, light, u, p, st, 0, x);
        update_st(adj, u, p, st, 0, -1);  // remove the subtree from st.
    }
    return res;
}
