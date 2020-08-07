#pragma once
#include <cpplib/stdinc.hpp>

vector<int> lcs(const vector<int> &a, const vector<int> &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dis(n + 1, vector<int>(m + 1));
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= m; ++j) {
            if(!i or !j)
                dis[i][j] = max(i, j);
            else {
                dis[i][j] = min({(a[i - 1] == b[j - 1] ? dis[i - 1][j - 1] : INF),
                    dis[i][j - 1] + 1,
                    dis[i - 1][j] + 1});
            }
        }
    }
    vector<int> res;
    for(int i = n, j = m; i and j;) {
        if(a[i - 1] == b[j - 1]) {
            res.emplace_back(a[i - 1]);
            i--;
            j--;
        }
        else if(dis[i - 1][j] <= dis[i][j - 1])
            i--;
        else
            j--;
    }
    reverse(all(res));
    return res;
}
