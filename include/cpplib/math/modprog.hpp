#pragma once
#include <cpplib/math/modop.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Modular Sum of Arithmetic Progression.
 *
 * Computes the sum of an arithmetic
 * progression of size n, mod m.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
uint modsum_ap(const int a, const int d, const uint n, const uint m = MOD)
{
    assert(n > 0 and m > 0);
    return moddiv(modmul(modadd(modmul(2, a, m), modmul(d, n - 1, m), m), n, m), 2, m);
}

/**
 * Modular Sum of Geometric Progression.
 *
 * Computes the sum of a geometric
 * progression of size n, mod m.
 *
 * Time Complexity: O(log(n) + log(m)).
 * Space Complexity: O(1).
 */
uint modsum_gp(const int a, const int r, const uint n, const uint m = MOD)
{
    assert(n > 0 and m > 0);
    if(r == 1)
        return modmul(a, n, m);
    return moddiv(modmul(a, modsub(1, modexp(r, n, m), m), m), 1 - r, m);
}
