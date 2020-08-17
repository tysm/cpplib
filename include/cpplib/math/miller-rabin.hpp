#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Modular Multiplication.
 *
 * Computes a*b%m.
 *
 * Note: if __uint128_t is present, the time
 * complexity is actually O(1).
 *
 * Time Complexity: O(log(mod(b, m))).
 * Space Complexity: O(1).
 */
static uint modmul(const uint a, const uint b, const uint m = MOD)
{
    assert(m > 0);
    uint mod_a = a % m, mod_b = b % m;
#ifdef __SIZEOF_INT128__
    return (__uint128_t)mod_a * mod_b % m;
#else
    if(mod_a < mod_b)
        return modmul(mod_b, mod_a, m);
    uint acc = mod_a, res = 0;
    for(; mod_b > 0; mod_b >>= 1) {
        if(mod_b & 1)
            res = (res + acc) % m;
        acc = (acc * 2) % m;
    }
    return res;
#endif
}

/**
 * Modular Binary Exponentiation.
 *
 * Computes pow(b, e)%m.
 *
 * Note: if __uint128_t is present, the time
 * complexity is actually O(log(e)).
 *
 * Time Complexity: O(log(e)*log(m)).
 * Space Complexity: O(1).
 */
static uint modexp(const uint b, uint e, const uint m = MOD)
{
    assert(m > 0);
    uint mod_b = b % m, res = 1;
    for(; e > 0; e >>= 1) {
        if(e & 1)
            res = modmul(res, mod_b, m);
        mod_b = modmul(mod_b, mod_b, m);
    }
    return res;
}

/**
 * Miller-Rabin Deterministic Primality Test.
 *
 * Returns true when x is prime, false
 * otherwise.
 *
 * Note: if __uint128_t is present, the time
 * complexity is actually O(pow(log(x), 2)).
 *
 * Time Complexity: O(pow(log(x), 3)).
 * Space Complexity: O(1).
 */
bool is_prime(const uint x)
{
    if(x < 2)
        return false;

    uint r = 0, d = x - 1;
    for(; (d & 1) == 0; d >>= 1)
        r++;

    for(uint i: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if(x == i)
            return true;

        uint v = modexp(i, d, x);
        if(v == 1 or v == x - 1)
            continue;

        bool check = true;
        for(uint j = 1; j < r and check; ++j) {
            v = modmul(v, v, x);
            if(v == x - 1)
                check = false;
        }
        if(check)
            return false;
    }
    return true;
}
