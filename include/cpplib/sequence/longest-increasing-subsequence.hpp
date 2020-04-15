#pragma once
#include <cpplib/stdinc.hpp>

vi lis(const vi &seq){
    int n = seq.size();
    vi d, idx, p(n, -1);

    for(int i=0; i<n; ++i){
        int j = upper_bound(d.begin(), d.end(), seq[i]) - d.begin();
        if(j == 0 or d[j-1] < seq[i]){
            if(j == d.size()){
                d.pb(seq[i]);
                idx.pb(i);
            }
            else{
                d[j] = seq[i];
                idx[j] = i;
            }
            if(j != 0)
                p[i] = idx[j-1];
        }
    }

    vi ans;
    for(int i=idx[d.size()-1]; i != -1; i = p[i])
        ans.pb(seq[i]);
    reverse(ans.begin(), ans.end());
    return ans;
}
