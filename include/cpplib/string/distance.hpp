#pragma once
#include <cpplib/stdinc.hpp>

vector<vector<int> > distance(const string &a, const string &b, bool transposition = false) {
    int n = a.size(), m = b.size();
    vector<vector<int> > dis(n + 1, vector<int>(m + 1));
    for(int i = 0; i <= n; ++i)
        dis[i][0] = i;
    for(int j = 0; j <= m; ++j)
        dis[0][j] = j;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            dis[i][j] = min({dis[i - 1][j - 1] + (int)(a[i - 1] != b[j - 1]),
                dis[i][j - 1] + 1,
                dis[i - 1][j] + 1});
            if(!transposition)
                continue;
            else if(i > 1 and j > 1 and a[i - 1] == b[j - 2] and a[i - 2] == b[j - 1])
                dis[i][j] = min(dis[i][j], dis[i - 2][j - 2] + 1);
        }
    }
    return dis;
}
