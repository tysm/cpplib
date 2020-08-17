#pragma once
#include <cpplib/math/miller-rabin.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Wheel Prime Factorization.
 *
 * Computes the prime factorization of x.
 *
 * Time Complexity: O(sqrt(x)).
 * Space Complexity: O(log(x)).
 */
vector<pair<uint, uint> > factorization(uint x)
{
    assert(x > 0);
    vector<pair<uint, uint> > factors;
    for(uint p: {2, 3, 5}) {
        while(x % p == 0) {
            if(factors.empty() or factors.back().first != p)
                factors.emplace_back(p, 1);
            else
                factors.back().second++;
            x /= p;
        }
    }
    vector<uint> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    for(uint p = 7, i = 0; p * p <= x; p += increments[i++], i %= 8) {
        while(x % p == 0) {
            if(factors.empty() or factors.back().first != p)
                factors.emplace_back(p, 1);
            else
                factors.back().second++;
            x /= p;
        }
    }
    if(x > 1)  // x is prime.
        factors.emplace_back(x, 1);
    return factors;
}

/**
 * Count of Prime Factors.
 *
 * Counts the number of prime factors of x.
 *
 * Note: if __uint128_t is present, the time
 * complexity is actually O(cbrt(x) + pow(log(x), 2)).
 *
 * Time Complexity: O(cbrt(x) + pow(log(x), 3)).
 * Space Complexity: O(1).
 */
uint count_prime_factors(uint x)
{
    assert(x > 0);
    uint res = 0;
    for(uint p: {2, 3, 5}) {
        if(p * p * p > x)
            break;
        for(; x % p == 0; x /= p)
            res++;
    }

    vector<uint> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    for(uint p = 7, i = 0; p * p * p <= x; p += increments[i++], i %= 8) {
        for(; x % p == 0; x /= p)
            res++;
    }
    if(x == 1)
        return res;

    if(is_prime(x))  // x is prime.
        res++;
    else  // sqrt(x) is prime or x is multiple of two other primes.
        res += 2;
    return res;
}

/**
 Count of Prime Factors.
 *
 * Counts the number of prime factors of x,
 * given its prime factorization.
 *
 * Time Complexity: O(log(x)).
 * Space Complexity: O(1).
 */
uint count_prime_factors(const vector<pair<uint, uint> > &factors)
{
    uint res = 0;
    for(auto f: factors)
        res += f.second;
    return res;
}
