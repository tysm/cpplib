#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Combination or Binomial Coefficient.
 *
 * Computes C(n, k), the number
 * in the n-th row and k-th column
 * of the Pascal's triangle.
 *
 * Time Complexity: O(k).
 * Space Complexity: O(1).
 */
uint C(const uint n, const uint k)
{
    assert(k <= n);
    double res = 1;
    for(uint i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;
    return res + 0.01;
}

/**
 * Permutation.
 *
 * Computes P(n, k).
 *
 * Time Complexity: O(n).
 * Space Complexity: O(1).
 */
uint P(const uint n, const uint k)
{
    assert(k <= n);
    uint res = 1;
    for(uint i = n; i > n - k; --i)
        res *= i;
    return res;
}

/**
 * Fibonacci Number.
 *
 * Computes the n-th and n+1-th
 * fibonacci numbers.
 *
 * Time Complexity: O(log(n)).
 * Space Complexity: O(log(n)).
 */
static pair<uint, uint> _fib(const uint n)
{
    if(n == 0)
        return {0, 1};
    pair<uint, uint> p = _fib(n >> 1);
    uint c = p.first * (2 * p.second - p.first), d = p.first * p.first + p.second * p.second;
    if(n & 1)
        return {d, c + d};
    return {c, d};
}

/**
 * Fibonacci Number.
 *
 * Computes the n-th fibonacci number.
 *
 * Time Complexity: O(log(n)).
 * Space Complexity: O(log(n)).
 */
uint fib(const uint n)
{
    return _fib(n).first;
}
