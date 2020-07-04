#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Binary Exponentiation.
 *
 * Computes pow(b, e).
 *
 * Time Complexity: O(log(e)).
 * Space Complexity: O(1).
 */
int bexp(int b, uint e){
    int res = 1;
    for(; e > 0; e >>= 1){
        if(e & 1)
            res *= b;
        b *= b;
    }
    return res;
}

/**
 * Binary Exponentiation.
 *
 * Note: this is the same algorithm as the
 * one above, but with b as double.
 *
 * Time Complexity: O(log(e)).
 * Space Complexity: O(1).
 */
double bexp(double b, uint e){
    double res = 1;
    for(; e > 0; e >>= 1){
        if(e & 1)
            res *= b;
        b *= b;
    }
    return res;
}
