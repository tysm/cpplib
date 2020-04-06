#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Lyndon Factorization.
 *
 * Computes the Lyndon factorization of the
 * given string and returns the bounds of
 * each factor.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the string.
 */
vii lyndon_factorization(const string &s){
    int n = s.size();
    vii factors;
    int i = 0;
    while(i < n){
        int j = i+1, k = i;
        while(j < n and s[k] <= s[j]){
            if(s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while(i <= k){
            factors.pb({i, i + j - k - 1});
            i += j - k;
        }
    }
    return factors;
}
