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
    LCA(const vvi &adj, const int root) :
        root(root), adj(adj),
        up(adj.size(), vi(ceil(log2(adj.size())), -1)),
        height(adj.size(), -1)
    {
        height[root] = 0;
        preprocess(-1, root);
    }

    /**
     * Computes the LCA of two nodes.
     *
     * Time Complexity: O(log(max(a, b))).
     * Space Complexity: O(1).
     */
    int query(int a, int b) const
    {
        if(height[a] > height[b])
            swap(a, b);
        while(height[b] > height[a])
            b = up[b][log2(height[b] - height[a])];
        if(a == b)
            return a;
        for(int i=up[a].size()-1; i>=0; i--){
            if(up[a][i] != up[b][i]){
                a = up[a][i];
                b = up[b][i];
            }
        }
        return up[a][0];
    }

    /**
     * Computes the distance between two nodes.
     *
     * Time Complexity: O(log(max(a, b))).
     * Space Complexity: O(1).
     */
    int distance(const int a, const int b) const
    {
        int l = query(a, b);
        return height[a] + height[b] - 2*height[l];
    }

private:
    void preprocess(const int p, const int u)
    {
        if(u != root){
            up[u][0] = p;
            for(int i=1, j=0; i<(int) up[u].size() and up[u][j] != -1; ++i, ++j)
                up[u][i] = up[up[u][j]][j];
            height[u] = height[p] + 1;
        }
        for(int v : adj[u]){
            if(v == p)
                continue;
            preprocess(u, v);
        }
    }

    int root;
    vvi adj, up;
    vi height;
};
