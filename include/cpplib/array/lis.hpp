#pragma once
#include <cpplib/stdinc.hpp>

vector<int> lis(const vector<int> &seq)
{
    int n = seq.size();
    vector<int> d, idx, p(n, -1);

    for(int i = 0; i < n; ++i) {
        int j = upper_bound(all(d), seq[i]) - d.begin();  // use lower_bound to get non-decreasing.
        if(j == 0 or d[j - 1] < seq[i]) {
            if(j == d.size()) {
                d.emplace_back(seq[i]);
                idx.emplace_back(i);
            }
            else {
                d[j] = seq[i];
                idx[j] = i;
            }
            if(j != 0)
                p[i] = idx[j - 1];
        }
    }

    vector<int> res;
    for(int i = idx[d.size() - 1]; i != -1; i = p[i])
        res.emplace_back(seq[i]);
    reverse(all(res));
    return res;
}
