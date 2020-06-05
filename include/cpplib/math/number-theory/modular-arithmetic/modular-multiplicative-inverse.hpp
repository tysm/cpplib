#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/linear-diophantine-equation.hpp>

/**
 * Modular Multiplicative Inverse.
 *
 * Computes the modular multiplicative
 * inverse of a with mod m.
 *
 * Time Complexity: O(log(min(a, m))).
 * Space Complexity: O(log(min(a, m))).
 */
int mmi(const int a, const int m = M){
    assert(gcd(a, m) == 1); // does not exists, a and m aren't coprimes.
    return mod(egcd(a, m).ss.ff, m);
}

/**
 * Modular Multiplicative Inverse DP.
 *
 * Computes the modular multiplicative
 * inverse for each natural <= n with mod m.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 */
vi mmidp(const int n = MAX, const int m = M){
    // assert(isprime(m));
    assert(n <= m);
    vi inv(n+1);
    inv[1] = 1;
    for(int i=2; i<=n; ++i)
        inv[i] = mod(-(m/i)*inv[m%i], m);
    return inv;
}
