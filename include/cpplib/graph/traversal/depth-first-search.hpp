#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Depth First Search.
 *
 * Performs a Depth First Search in a graph
 * given its vertex adjacencies.
 *
 * Time Complexity: O(n + m).
 * Space Complexity: O(n).
 * Where n is the size of the graph and m is the quantity of edges.
 */
void dfs(const int u, const vvi &adj, vb &vis){
    vis[u] = true;
    for(int v : adj[u]){
        if(vis[v])
            continue;
        dfs(v, adj, vis);
    }
}
