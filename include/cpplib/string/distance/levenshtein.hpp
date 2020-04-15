#pragma once
#include <cpplib/stdinc.hpp>

vvi distance(const string &a, const string &b){
    int n = a.size(), m = b.size();
    vvi dis(n+1, vi(m+1));
    for(int i=0; i<=n; ++i){
        for(int j=0; j<=m; ++j){
            if(!i or !j)
                dis[i][j] = max(i, j);
            else{
                dis[i][j] = min({
                    dis[i-1][j-1] + (int)(a[i-1] != b[j-1]),
                    dis[i][j-1]+1,
                    dis[i-1][j]+1
                });
            }
        }
    }
    return dis;
}
