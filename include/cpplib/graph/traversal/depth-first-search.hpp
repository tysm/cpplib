#pragma once
#include <cpplib/header>

/**
 * Depth First Search.
 * TODO validate.
 *
 * Time Complexity: O(n + m).
 * Where n is the size of the graph and m is the quantity of edges.
 */
void dfs(int v, vector<vi> &adj, vector<bool> &vis){
    vis[v] = true;
    for(int u : adj[v]){
        if(vis[u])
            continue;
        dfs(u);
    }
}
