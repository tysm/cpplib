#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Z-Function.
 *
 * Computes the length of the longest
 * commom prefix between the given string
 * and each of its proper suffixes.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the string.
 */
vector<int> z_function(const string &s)
{
    int n = s.size();
    vector<int> z(n);
    for(int i = 1, l = 0, r = 0; i < n; ++i) {
        if(i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < n and s[z[i]] == s[i + z[i]])
            z[i]++;
        if(i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
