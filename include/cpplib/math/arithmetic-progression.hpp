#pragma once
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
int sap(const int a0, const int an, const int n){
    return ((a0 + an)*n)/2;
}

/**
 * Sum of Arithmetic Progression with mod.
 *
 * Computes the sum of an arithmetic
 * progression of size n, mod m.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
int sapm(const int a0, const int an, const int n, const int m = M){
    if(n%2 == 0)
        return mod(mod(a0 + an, m)*mod(n/2), m);
    return mod(mod((a0 + an)/2, m)*mod(n, m), m);
}
