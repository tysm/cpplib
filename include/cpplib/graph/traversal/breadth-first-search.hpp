#pragma once
#include <cpplib/header>

/**
 * Breadth First Search
 * TODO validate.
 *
 * Note: in orther to retrieve the shortest path
 * we can store the predecessor of any vertex when
 * a successful relaxation occurs.
 *
 * Time Complexity: O(n + m).
 * Where n is the size of the graph and m is the quantity of edges.
 */
vi bfs(int s, vector<vi> &adj){
    vi dis(adj.size(), INF); dis[s] = 0; // distance from s to s is 0.
    queue<int> q; q.push(s);

    while(!q.empty()){
        int u = q.front(); q.pop();

        for(int v : adj[u]){
            if(dis[v] != INF)
                continue;
            dis[v] = dis[u] + 1;
            q.push(v);
        }
    }
    return dis;
}
