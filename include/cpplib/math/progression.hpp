#pragma once
#include <cpplib/math/exponentiation.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Sum of Arithmetic Progression.
 *
 * Computes the sum of an arithmetic
 * progression of size n.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T>
T sum_ap(const T a, const T d, const uint n)
{
    assert(n > 0);
    T aux = 2 * a + d * (n - 1);
    if(n & 1 == 0)
        return aux * (n / 2);
    return (aux / 2) * n;
}

/**
 * Sum of Geometric Progression.
 *
 * Computes the sum of a geometric
 * progression of size n.
 *
 * Time Complexity: O(log(n)).
 * Space Complexity: O(1).
 */
template<typename T>
T sum_gp(const T a, const T r, const uint n)
{
    assert(n > 0);
    if(r == 1)
        return a * n;
    return (a * (1 - exp(r, n))) / (1 - r);
}

/**
 * Sum of Finite Geometric Progression.
 *
 * Computes the sum of a finite geometric
 * progression.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
double sum_gp(const double a, const double r)
{
    assert(abs(r) < 1);
    return a / (1 - r);
}
