#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Sieve of Eratosthenes.
 *
 * Computes the prime numbers until
 * an upper bound.
 *
 * Time Complexity: O(n*log(log(n))).
 * Space Complexity: O(n).
 * Where n is the upper bound.
 */
class Sieve
{
public:
    Sieve(const uint sieve_u) :
        sieve_u(sieve_u), prime((sieve_u + 1) / 2, true) {
        prime[0] = false;
        for(uint i = 3; i * i <= sieve_u; i += 2) {
            if(!prime[i / 2])
                continue;
            for(uint j = i * i; j <= sieve_u; j += i) {
                if(j & 1)
                    prime[j / 2] = false;
            }
        }
    }

    /**
     * Checks if a number is prime.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    bool is_prime(const uint x) const {
        assert(x <= sieve_u);
        return x & 1 ? prime[x / 2] : x == 2;
    }

private:
    uint sieve_u;        // sieve upper bound.
    vector<bool> prime;  // is_prime as boolean array.
};
