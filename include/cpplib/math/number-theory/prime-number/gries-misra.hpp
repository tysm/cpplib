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
    Sieve(const uint upper_bound) :
        upper_bound(upper_bound), min_prime_factor(upper_bound+1)
    {
        for(uint i = 2; i <= upper_bound; ++i){
            if(!min_prime_factor[i]){
                min_prime_factor[i] = i;
                primes.emplace_back(i);
            }
            for(uint p : primes){
                if(p > min_prime_factor[i] or i*p > upper_bound)
                    break;
                min_prime_factor[i*p] = p;
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
        assert(0 < x and x <= upper_bound);
        vector<pair<uint, uint> > factors;
        for(; x > 1; x /= min_prime_factor[x]){
            uint p = min_prime_factor[x];
            if(factors.empty() or factors.back().first != p)
                factors.emplace_back(p, 1);
            else
                factors.back().second++;
        }
        return factors;
    }

    /**
     * Checks if a number is prime.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    bool is_prime(const uint x) const
    {
        assert(0 < x and x <= upper_bound);
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
        return upper_bound;
    }

private:
    uint upper_bound;
    vector<uint> min_prime_factor, primes;
};
