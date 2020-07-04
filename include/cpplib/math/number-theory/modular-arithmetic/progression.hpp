#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/modular-arithmetic/operation.hpp>

/**
 * Modular Sum of Arithmetic Progression.
 *
 * Computes the sum of an arithmetic
 * progression of size n, mod m.
 *
 * Time Complexity: O(log(m)).
 * Space Complexity: O(1).
 */
int modsum_ap(const int a, const int d, const int n, const int m = M){
    assert(n > 0);
    return moddiv(modmul((2*mod(a, m))%m + modmul(d, n-1, m), n, m), 2, m);
}

/**
 * Modular Sum of Geometric Progression.
 *
 * Computes the sum of a geometric
 * progression of size n, mod m.
 *
 * Time Complexity: O(log(m)).
 * Space Complexity: O(1).
 */
int modsum_gp(const int a, const int r, const int n, const int m = M){
    assert(n > 0);
    if(r == 1)
        return modmul(a, n, m);
    return moddiv(modmul(a, 1 - modexp(r, n, m), m), 1 - r, m);
}
