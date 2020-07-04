#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/exponentiation.hpp>

/**
 * Sum of Arithmetic Progression.
 *
 * Computes the sum of an arithmetic
 * progression of size n.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
int sum_ap(const int a, const int d, const int n){
    assert(n > 0);
    int aux = 2*a + d*(n-1);
    if(aux%2 == 0)
        return (aux/2)*n;
    return aux*(n/2);
}

/**
 * Sum of Arithmetic Progression.
 *
 * Note: this is the same algorithm as the
 * one above, but with double parameters.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
double sum_ap(const double a, const double d, const int n){
    assert(n > 0);
    double aux = 2*a + d*(n-1);
    if(n%2 == 0)
        return aux*(n/2);
    return (aux*n)/2;
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
int sum_gp(const int a, const int r, const int n){
    assert(n > 0);
    if(r == 1)
        return a*n;
    int aux = 1 - bexp(r, n);
    if(a%(1 - r) == 0)
        return (a/(1 - r))*aux;
    return a*(aux/(1- r));
}

/**
 * Sum of Geometric Progression.
 *
 * Note: this is the same algorithm as the
 * one above, but with double parameters.
 *
 * Time Complexity: O(log(n)).
 * Space Complexity: O(1).
 */
double sum_gp(const double a, const double r, const int n){
    assert(n > 0);
    if(r == 1)
        return a*n;
    return (a*(1 - bexp(r, n)))/(1 - r);
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
double sum_gp(const double a, const double r){
    assert(abs(r) < 1);
    return a/(1 - r);
}
