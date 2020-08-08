#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/string/pi-function.hpp>

/**
 * Knuth Morris Pratt.
 *
 * Computes the occurrences of a string s
 * (pattern) in another string t (text).
 *
 * Time Complexity: O(n + m).
 * Space Complexity: O(n + m).
 * Where n is the size of the pattern and m is the size of the text.
 */
vector<int> kmp(const string &s, const string &t) {
    int n = s.size(), m = t.size();
    vector<int> pi = prefix_function(s + '#'), ans;
    for(int i = 0, j = 0; i < m; ++i) {
        while(j > 0 and t[i] != s[j])
            j = pi[j - 1];
        if(t[i] == s[j])
            j++;
        if(j == n)
            ans.emplace_back(i + 1 - n);
    }
    return ans;
}
