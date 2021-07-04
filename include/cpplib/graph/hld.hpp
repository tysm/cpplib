#pragma once
#include <cpplib/stdinc.hpp>

template<typename SegTree, typename T>
class HLD
{
public:
    HLD(const vector<vector<int> > &adj, const vector<T> &values, const int root) :
        chain_id(adj.size(), -1), id_in_tree(adj.size(), -1), subtree_size(adj.size()), parent(adj.size(), -1)
    {
        compute_size(root, adj);
        vector<T> tree;
        dfs(root, true, adj, values, tree);
        st = SegTree(tree);
    }

    vector<T> query(const int u)
    {
        return query(u, u);
    }

    vector<T> query(int u, int v)
    {
        vector<T> res;
        while(chain_id[u] != chain_id[v]) {
            if(chain_id[u] > chain_id[v])
                swap(u, v);
            int head = chain_head[chain_id[v]];
            res.emplace_back(st.query(id_in_tree[head], id_in_tree[v]));
            v = parent[head];
        }
        if(subtree_size[u] < subtree_size[v])
            swap(u, v);
        res.emplace_back(st.query(id_in_tree[u], id_in_tree[v]));
        return res;
    }

    void update(const int u, const T delta)
    {
        return update(u, u, delta);
    }

    void update(int u, int v, const T delta)
    {
        while(chain_id[u] != chain_id[v]) {
            if(chain_id[u] > chain_id[v])
                swap(u, v);
            int head = chain_head[chain_id[v]];
            st.update(id_in_tree[head], id_in_tree[v], delta);
        }
        if(subtree_size[u] < subtree_size[v])
            swap(u, v);
        st.update(id_in_tree[u], id_in_tree[v], delta);
    }

private:
    void compute_size(const int u, const vector<vector<int> > &adj)
    {
        subtree_size[u] = 1;
        for(int v: adj[u]) {
            if(v == parent[u])
                continue;
            parent[v] = u;
            compute_size(v, adj);
            subtree_size[u] += subtree_size[v];
        }
    }

    void dfs(const int u, const bool new_chain, const vector<vector<int> > &adj, const vector<T> &values, vector<T> &tree)
    {
        if(new_chain) {
            chain_id[u] = number_of_chains;
            chain_head.emplace_back(u);
            number_of_chains++;
        }
        else
            chain_id[u] = chain_id[parent[u]];
        id_in_tree[u] = tree.size();
        tree.emplace_back(values[u]);

        int max_size = 0, heavy = -1;
        for(int v: adj[u]) {
            if(v == parent[u])
                continue;
            if(subtree_size[v] > max_size) {
                max_size = subtree_size[v];
                heavy = v;
            }
        }

        if(heavy != -1)
            dfs(heavy, false, adj, values, tree);  // heavy edge.

        for(int v: adj[u]) {
            if(v == parent[u] or v == heavy)
                continue;
            dfs(v, true, adj, values, tree);  // light edge.
        }
    }

    int number_of_chains = 0;
    vector<int> chain_id, chain_head, id_in_tree, subtree_size, parent;
    SegTree st;
};
