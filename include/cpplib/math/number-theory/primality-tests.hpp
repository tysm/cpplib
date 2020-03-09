#pragma once
#include <cpplib/header.hpp>

using u64 = uint64_t;
using u128 = __uint128_t;

/**
 * Trivial Division.
 *
 * Returns true when n is prime,
 * false otherwise.
 *
 * Time Complexity: O(sqrt(n)).
 */
bool isprime(int n){
    for(int i=2; i*i<=n; ++i){
        if(n%i == 0)
            return false;
    }
    return true;
}

/**
 * Miller-Rabin Deterministic Test.
 *
 * Returns true when n is prime,
 * false otherwise.
 *
 * Time Complexity: O(log(n)).
 */
bool isprime(u64 n);
