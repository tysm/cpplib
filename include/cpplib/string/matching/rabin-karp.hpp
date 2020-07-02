#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/data-structure/rolling-hash.hpp>
#include <cpplib/utility/random.hpp>

/**
 * Rabin Karp.
 *
 * Computes the occurrences of a string s
 * (pattern) in another string t (text).
 *
 * Note: if the strings are composed only
 * of lowercase letters of the English
 * alphabet, the hash base could be 31.
 * If the strings are composed of both
 * uppercase and lowercase letters the
 * base could be 53.
 *
 * Time Complexity: O(n + m).
 * Space Complexity: O(n + m).
 * Where n is the size of the pattern and m is the size of the text.
 */
vi rabin(const string &s, const string &t, const char offset = 'a'){
    int n = s.size(), m = t.size();
    if(n > m)
        return vi();

    uint base = randuint16(1);
    RollingHash hs(s, base, offset), ht(t, base, offset);

    vi ans;
    for(int i=0; i<=m-n; ++i){
        if(hs.hash() == ht.query(i, i+n-1))
            ans.pb(i);
    }
    return ans;
}
