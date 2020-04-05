#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/data-structures/rolling-hash.hpp>

/**
 * Rabin Karp.
 *
 * Computes the occurrences of a string s
 * (pattern) in another string t (text).
 *
 * Note: here we assume that the strings
 * are composed only of lowercase letters
 * of the English alphabet, thus the hash
 * base is 31. If the strings are composed
 * of both uppercase and lowercase letters
 * the base must be 53.
 *
 * Time Complexity: O(n + m).
 * Space Complexity: O(n + m).
 * Where n is the size of the pattern and m is the size of the text.
 */
vi rabin(const string &s, const string &t){
    int n = s.size(), m = t.size();
    if(n > m)
        return vi();

    RollingHash hs(31), ht(31);
    for(char c:s)
        hs.pb(c-'a'+1);
    for(char c:t)
        ht.pb(c-'a'+1);

    vi ans;
    for(int i=0; i<=m-n; ++i){
        if(hs.hash() == ht.query(i, i+n-1))
            ans.pb(i);
    }
    return ans;
}
