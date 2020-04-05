#pragma once
#include <cpplib/stdinc.hpp>

using u64 = uint64_t;
using u128 = __uint128_t;

/**
 * Binary Exponentiation with mod.
 *
 * Note: this is the same algorithm as the
 * one codded in the lib, but it should be
 * used when the values are too large so
 * that some operations may cause overflow.
 *
 * Time Complexity: O(log(e)).
 * Space Complexity: O(log(e)).
 */
u64 ubexpm(u64 b, u64 e, const u64 m){
    b %= m;
    u64 res = 1;
    while(e > 0){
        if(e & 1)
            res = ((u128)res*b)%m;
        b = ((u128)b*b)%m;
        e >>= 1;
    }
    return res;
}

/**
 * Miller-Rabin Deterministic Test.
 *
 * Returns true when n is prime, false
 * otherwise.
 *
 * Time Complexity: O(log(n)).
 * Space Complexity: O(1).
 */
bool isprime(const u64 n){
    if(n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while((d & 1) == 0){
        r++;
        d >>= 1;
    }

    for(int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if(n == i)
            return true;

        u64 x = ubexpm(i, d, n);
        if(x == 1 or x == n - 1)
            continue;

        bool check = true;
        for(int j=1; j<r and check; ++j){
            x = ((u128)x*x)%n;
            if(x == n - 1)
                check = false;
        }
        if(check)
            return false;
    }
    return true;
}
