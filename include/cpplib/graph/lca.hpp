#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Lowest Common Ancestor.
 *
 * Given a tree, computes the LCA of two
 * nodes online.
 *
 * Note: it's also usefull to compute
 * distances.
 *
 * Time Complexity: O(n*log(n)).
 * Space Complexity: O(n*log(n)).
 * Where n is the size of the given tree.
 */
class LCA
{
public:
    LCA(const int n, const vector<vector<int> > &adj, const int root) :
        tree_size(n), root(root), height(n, -1), _log2(n + 1, 0),
        up(n, vector<int>((int)ceil(log2(n)), -1))
    {
        for(int i = 2; i <= n; ++i)
            _log2[i] = _log2[i / 2] + 1;

        height[root] = 0;
        preprocess(adj, -1, root);
    }

    LCA(const vector<vector<int> > &adj, const int root) :
        LCA(adj.size(), adj, root) {}

    /**
     * Computes the LCA of two nodes.
     *
     * Time Complexity: O(log(max(height[a], height[b]))).
     * Space Complexity: O(1).
     */
    int query(int a, int b) const
    {
        assert(a < tree_size);
        assert(b < tree_size);
        if(height[a] > height[b])
            swap(a, b);
        while(height[b] > height[a])
            b = up[b][_log2[height[b] - height[a]]];
        if(a == b)
            return a;
        for(int i = up[a].size() - 1; i >= 0; i--) {
            if(up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
            assert(min(a, b) >= 0);
        }
        return up[a][0];
    }

    /**
     * Computes the distance between two nodes.
     *
     * Time Complexity: O(log(max(height[a], height[b]))).
     * Space Complexity: O(1).
     */
    int distance(const int a, const int b) const
    {
        assert(a < tree_size);
        assert(b < tree_size);
        int l = query(a, b);
        return height[a] + height[b] - 2 * height[l];
    }

    /**
     * Computes the i-th ancestor of a node.
     *
     * Time Complexity: O(log(height[u])).
     * Space Complexity: O(1).
     */
    int ancestor(int u, const int i = 1) const
    {
        assert(u < tree_size);
        assert(0 < i and i <= height[u]);
        int h = height[u] - i;
        while(height[u] > h)
            u = up[u][_log2[height[u] - h]];
        return u;
    }

private:
    void preprocess(const vector<vector<int> > &adj, const int p, const int u)
    {
        assert(u < tree_size);
        if(u != root) {
            up[u][0] = p;
            for(int i = 1, j = 0; i < (int)up[u].size() and up[u][j] != -1; ++i, ++j)
                up[u][i] = up[up[u][j]][j];
            height[u] = height[p] + 1;
        }
        for(int v: adj[u]) {
            if(v == p)
                continue;
            preprocess(adj, u, v);
        }
    }

    int tree_size, root;
    vector<int> height, _log2;
    vector<vector<int> > up;
};
