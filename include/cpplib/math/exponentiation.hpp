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
template<typename T>
T exp(T b, uint e)
{
    T res = 1;
    for(; e > 0; e >>= 1) {
        if(e & 1)
            res *= b;
        b *= b;
    }
    return res;
}
