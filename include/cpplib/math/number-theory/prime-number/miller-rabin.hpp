#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/modular-arithmetic/operation.hpp>

/**
 * Miller-Rabin Deterministic Primality Test.
 *
 * Returns true when x is prime, false
 * otherwise.
 *
 * Time Complexity: O(pow(log(x), 2)).
 * Space Complexity: O(1).
 */
bool is_prime(const int x){
    assert(x >= 0);
    if(x < 2)
        return false;

    int r = 0, d = x - 1;
    for(; (d & 1) == 0; d >>= 1)
        r++;

    for(int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if(x == i)
            return true;

        int v = modexp(i, d, x);
        if(v == 1 or v == x - 1)
            continue;

        bool check = true;
        for(int j = 1; j < r and check; ++j){
            v = modmul(v, v, x);
            if(v == x - 1)
                check = false;
        }
        if(check)
            return false;
    }
    return true;
}
