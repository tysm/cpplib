#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Sieve of Eratosthenes.
 *
 * Computes the prime numbers until
 * an upper bound.
 *
 * Time Complexity: O(n*pow(log(n), 2)).
 * Space Complexity: O(n).
 * Where n is the upper bound.
 */
class Sieve
{
public:
    Sieve(const uint upper_bound) :
        upper_bound(upper_bound), prime((upper_bound+1)/2, true)
    {
        prime[0] = false;
        for(uint i = 3; i*i <= upper_bound; i += 2){
            if(!prime[i/2])
                continue;
            for(uint j = i*i; j <= upper_bound; j += i){
                if(j%2)
                    prime[j/2] = false;
            }
        }
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
        return x%2? prime[x/2] : x == 2;
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
    vector<bool> prime;
};
