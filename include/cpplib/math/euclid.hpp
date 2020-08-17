#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Euclidean GCD.
 *
 * Computes the greatest commom divisor of
 * two integers.
 *
 * Time Complexity: O(log(min(a, b))).
 * Space Complexity: O(1).
 */
uint gcd(uint a, uint b)
{
    for(; a != 0; a %= b)
        swap(a, b);
    return b;
}

/**
 * Extended Euclidean GCD.
 *
 * Besides computing the GCD it also returns
 * the roots of a*x + b*y = gcd(a, b).
 *
 * Time Complexity: O(log(min(a, b))).
 * Space Complexity: O(1).
 */
tuple<uint, int, int> extended_gcd(uint a, uint b)
{
    int x = 0, y = 1, x1 = 1, y1 = 0;
    while(a != 0) {
        uint q = b / a;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a, b) = make_tuple(b % a, a);
    }
    return make_tuple(b, x, y);
}

/**
 * Euclidean Derivated LCM.
 *
 * Time Complexity: O(log(min(a, b))).
 * Space Complexity: O(1).
 */
uint lcm(const uint a, const uint b)
{
    // same as a*b/gcd(a, b) but avoiding overflow.
    return a / gcd(a, b) * b;
}
