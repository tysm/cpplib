#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/prime-number/miller-rabin.hpp>

/**
 * Count of Divisors.
 *
 * Counts the number of divisors of x.
 *
 * Note: if __uint128_t is present, the time
 * complexity is actually O(cbrt(x) + pow(log(x), 2)).
 *
 * Time Complexity: O(cbrt(x) + pow(log(x), 3)).
 * Space Complexity: O(1).
 */
uint count_divisors(uint x){
    assert(x > 0);

    uint res = 1;
    for(uint p : {2, 3, 5}){
        if(p*p*p > x)
            break;
        uint cnt = 1;
        for(; x%p == 0; x /= p)
            cnt++;
        res *= cnt;
    }

    vector<uint> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    for(uint p = 7, i = 0; p*p*p <= x; p += increments[i++], i %= 8){
        uint cnt = 1;
        for(; x%p == 0; x /= p)
            cnt++;
        res *= cnt;
    }
    if(x == 1)
        return res;

    if(is_prime(x)) // x is prime.
        res *= 2;
    else if((uint)sqrt(x)*(uint)sqrt(x) == x) // sqrt(x) is prime.
        res *= 3;
    else // x is multiple of two other primes.
        res *= 4;
    return res;
}

/**
 * Count of Divisors.
 *
 * Counts the number of divisors of x, given
 * its prime factorization.
 *
 * Time Complexity: O(log(x)).
 * Space Complexity: O(1).
 */
uint count_divisors(const vector<pair<uint, uint> > &factors){
    uint res = 1;
    for(auto f : factors)
        res *= f.second+1;
    return res;
}
