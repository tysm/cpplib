#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Manacher.
 *
 * Computes the bounds of the longest
 * palindromic substring of the given
 * string.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the string.
 */
pair<int, int> manacher(const string &s)
{
    int n = s.size();
    pair<int, int> ans = {0, 0};
    vector<int> dp(n);
    for(int i = 0, l = 0, r = 0; i < n; ++i) {
        int k = (i > r ? 1 : min(dp[l + r - i] + 1, r - i + 1));
        while(i - k >= 0 and i + k < n and s[i - k] == s[i + k])
            k++;
        dp[i] = --k;
        if(i + k > r) {
            l = i - k;
            r = i + k;
            if(r - l > ans.second - ans.first)
                ans = {l, r};
        }
    }
    dp.assign(n, 0);
    for(int i = 0, l = 0, r = 0; i < n; ++i) {
        int k = (i > r ? 0 : min(dp[l + r - i + 1] + 1, r - i + 1));
        while(i - k - 1 >= 0 and i + k < n and s[i - k - 1] == s[i + k])
            k++;
        dp[i] = --k;
        if(i + k > r) {
            l = i - k - 1;
            r = i + k;
            if(r - l > ans.second - ans.first)
                ans = {l, r};
        }
    }
    return ans;
}
