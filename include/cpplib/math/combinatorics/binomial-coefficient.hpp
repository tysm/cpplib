#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Binomial Coefficient.
 *
 * Computes C(n, k), the number
 * in the n-th row and k-th column
 * of the Pascal's triangle.
 *
 * Time Complexity: O(k).
 * Space Complexity: O(1).
 */
uint binc(const uint n, const uint k){
    assert(k <= n);
    double res = 1;
    for(uint i=1; i<=k; ++i)
        res = res*(n - k + i)/i;
    return res + 0.01;
}
