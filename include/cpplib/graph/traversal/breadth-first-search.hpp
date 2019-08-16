#pragma once
#include <cpplib/header>

/**
 * Breadth First Search
 * TODO validate.
 *
 * Time Complexity: O(n + m).
 * Where n is the size of the graph and m is the quantity of edges.
 */
vi bfs(int s, vector<vi> &adj){
    vi dis(adj.size(), INF); dis[s] = 0; // distance from s to s is 0.
    queue<int> q; q.push(s);

    while(!q.empty()){
        int v = q.front(); q.pop();

        for(int u : adj[v]){
            if(dis[u] != INF)
                continue;
            dis[u] = dis[v] + 1;
            q.push(u);
        }
    }
    return dis;
}
