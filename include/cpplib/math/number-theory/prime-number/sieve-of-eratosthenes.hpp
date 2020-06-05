#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Sieve of Eratosthenes.
 *
 * Computes the prime numbers until
 * an upper bound.
 *
 * Time Complexity: O(n*log(n)*log(n)).
 * Space Complexity: O(n).
 * Where n is the upper bound.
 */
class Sieve
{
public:
    Sieve(const size_t upper_bound) :
        is_prime((upper_bound+1)/2, true), sz(upper_bound)
    {
        is_prime[0] = false;
        for(size_t i=3; i*i<=upper_bound; i+=2){
            if(!is_prime[i/2])
                continue;
            for(size_t j=i*i; j<=upper_bound; j+=i){
                if(j%2)
                    is_prime[j/2] = false;
            }
        }
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
        return x%2? is_prime[x/2] : x == 2;
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
    vb is_prime;
    size_t sz;
};
