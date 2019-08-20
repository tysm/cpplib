#pragma once
#include <cpplib/header>

/**
 * Floyd Warshall.
 * TODO validate.
 *
 * Time Complexity: O(exp(n, 3)).
 * Where n is the size of the graph.
 */
vector<vi> floyd(vector<vi> &adj){
    vector<vi> dis(adj);
    for(int i=0; i<dis.size(); ++i){
        for(int j=0; j<dis.size; ++j){
            if(!adj[i][j])
                adj[i][j] = INF;
        }
    }
    for(int k=0; k<dis.size(); ++k){
        for(int i=0; i<dis.size(); ++i){
            for(int j=0; j<dis.size(); ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        }
    }
    return dis;
}
