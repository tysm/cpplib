#pragma once
#include <cpplib/header>

/**
 * Depth First Search.
 * TODO validate.
 *
 * Time Complexity: O(n + m).
 * Where n is the size of the graph and m is the quantity of edges.
 */
void dfs(int u, vector<vi> &adj, vector<bool> &vis){
    vis[u] = true;
    for(int v : adj[u]){
        if(vis[v])
            continue;
        dfs(v);
    }
}
