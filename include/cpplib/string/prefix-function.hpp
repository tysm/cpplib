#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Prefix Function.
 *
 * Computes the length of the longest
 * proper prefix which is also a suffix for
 * each prefix of a given string.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the string.
 */
vi prefix_function(const string &s){
    int n = s.size();
    vi pi(n);
    for(int i=1; i<n; ++i){
        int j = pi[i-1];
        while(j > 0 and s[i] != s[j])
            j = pi[j-1];
        if(s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
