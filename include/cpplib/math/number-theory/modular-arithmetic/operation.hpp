#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/euclid.hpp>

///
// It's ok to say that the following
// functions run in O(log(m)) of time:
//   - modmul;
//   - inverse;
//   - moddiv.
///

/**
 * Modulus.
 *
 * Computes the positive result of a%m.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
int mod(int a, const int m = M){
    a %= m;
    if(a < m)
        a += m;
    return a;
}

/**
 * Modular Multiplication.
 *
 * Computes a*b%m.
 *
 * Time Complexity: O(log(min(mod(a, m), mod(b, m)))).
 * Space Complexity: O(1).
 */
int modmul(const int a, const int b, const int m = M){
    if(mod(a, m) < mod(b, m))
        return modmul(b, a, m);
    int acc = mod(a, m), res = 0;
    for(int t = mod(b, m); t > 0; t >>= 1){
        if(t & 1)
            res = (res + acc)%m;
        acc = (acc*2)%m;
    }
    return res;
}

/**
 * Modular Multiplicative Inverse.
 *
 * Computes the modular multiplicative
 * inverse of a with mod m.
 *
 * Time Complexity: O(log(mod(a, m))).
 * Space Complexity: O(1).
 */
int inverse(const int a, const int m = M){
    auto aux = extended_gcd(mod(a, m), m);
    assert(get<0>(aux) == 1); // mod(a, m) and m must be coprimes.
    return mod(get<1>(aux), m);
}

/**
 * Modular Division.
 *
 * Computes a/b%m.
 *
 * Time Complexity: O(log(mod(b, m)) + log(min(mod(a, m), inverse(b, m)))).
 * Space Complexity: O(1).
 */
int moddiv(const int a, const int b, const int m = M){
    return modmul(mod(a, m), inverse(b, m), m);
}

/**
 * Modular Binary Exponentiation.
 *
 * Computes pow(b, e)%m.
 *
 * Time Complexity: O(log(e)*log(m)).
 * Space Complexity: O(1).
 */
int modexp(int b, uint e, const int m = M){
    int res = 1;
    for(; e > 0; e >>= 1){
        if(e & 1)
            res = modmul(res, b, m);
        b = modmul(b, b, m);
    }
    return res;
}
