#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Floyd Warshall.
 *
 * Computes the shortest path for all pairs
 * in a weighted graph given its adjacency
 * matrix.
 *
 * Note: here we assume the dis parameter
 * as the given adjacency matrix initially
 * and:
 * - dis[i][j] = INF if i and j aren't
 * adjacents for i,j in [0,n[ and i != j;
 * - dis[i][i] = 0 for i,j in [0,n[.
 *
 * Note: in orther to retrieve the shortest
 * path we can store the predecessor of
 * each vertex when a successful relaxation
 * occurs.
 *
 * Time Complexity: O(exp(n, 3)).
 * Space Complexity: O(exp(n, 2)).
 * Where n is the size of the graph.
 */
template<typename T>
vector<vector<T> > floyd(vector<vector<T> > dis, const T inf = LINF)
{
    int n = dis.size();
    for(int k = 0; k < n; ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(dis[i][k] > inf - EPS or dis[k][j] > inf - EPS)
                    continue;
                if(dis[i][k] + dis[k][j] <= dis[i][j] - EPS)
                    dis[i][j] = dis[i][k] + dis[k][j];
            }
        }
    }
    return dis;
}
