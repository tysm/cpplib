#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Sieve of Gries and Misra.
 *
 * Computes the prime numbers until
 * an upper bound and provides
 * number factorization.
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the upper bound.
 */
class Sieve
{
public:
    Sieve(const size_t upper_bound) :
        min_prime_factor(upper_bound+1), sz(upper_bound)
    {
        for(size_t i=2; i<=upper_bound; ++i){
            if(!min_prime_factor[i]){
                min_prime_factor[i] = i;
                primes.pb(i);
            }
            for(uint j : primes){
                if(j > min_prime_factor[i] or i*j > upper_bound)
                    break;
                min_prime_factor[i*j] = j;
            }
        }
    }

    /**
     * Computes the prime factorization of x.
     *
     * Time Complexity: O(log(x)).
     * Space Complexity: O(log(x)).
     */
    vector<pair<uint, uint> > factorization(uint x) const
    {
        assert(x <= sz);
        vector<pair<uint, uint> > factors;
        if(x >= 2){
            while(x != 1){
                uint factor = min_prime_factor[x];
                if(factors.empty() or factors.back().ff != factor)
                    factors.pb({factor, 1});
                else
                    factors.back().ss++;
                x /= factor;
            }
        }
        return factors;
    }

    /**
     * Checks if a number is prime.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    bool isprime(const uint x) const
    {
        assert(x <= sz);
        return x <= 1? false : min_prime_factor[x] == x;
    }

    /**
     * Return the computed prime numbers.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     */
    vector<uint> prime_numbers() const
    {
        return primes;
    }

    /**
     * Returns the upper bound.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    size_t size() const
    {
        return sz;
    }

private:
    vector<uint> min_prime_factor, primes;
    size_t sz;
};
