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
 * Where n is the sieve upper bound.
 */
class Sieve
{
public:
    Sieve(const uint sieve_u) :
        sieve_u(sieve_u), spf(sieve_u+1)
    {
        for(uint i = 2; i <= sieve_u; ++i){
            if(!spf[i]){
                spf[i] = i;
                primes.emplace_back(i);
            }
            for(uint p : primes){
                if(p > spf[i] or i*p > sieve_u)
                    break;
                spf[i*p] = p;
            }
        }
    }

    /**
     * Computes the prime numbers in the range
     * [l, r].
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     * Where n is the size of the segment range (i.e. r - l + 1).
     */
    void segment(const uint l, const uint r)
    {
        assert(l <= r and ceil(sqrt(r)) <= sieve_u);
        tie(segment_l, segment_u) = make_tuple(l, r);

        uint n = r - l + 1, lim = sqrt(r);
        segment_spf.assign(n, 0);
        segment_primes.clear();

        for(uint p : primes){
            if(p > lim)
                break;
            for(uint i = (p*p >= l? p*p - l : (p - l%p)%p); i < n; i += p){
                if(!segment_spf[i])
                    segment_spf[i] = p;
            }
        }

        for(uint i = l; i <= r; ++i){
            if(i < 2 or segment_spf[i - l])
                continue;
            segment_spf[i - l] = i;
            segment_primes.emplace_back(i);
        }
    }

    /**
     * Computes the prime factorization of x.
     *
     * Note: it's not viable to factorize numbers
     * > sieve_u.
     *
     * Time Complexity: O(log(x)).
     * Space Complexity: O(log(x)).
     */
    vector<pair<uint, uint> > factorization(uint x) const
    {
        assert(0 < x and x <= sieve_u);
        vector<pair<uint, uint> > factors;
        for(; x > 1; x /= spf[x]){
            uint p = spf[x];
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
     * Note: x must be <= sieve_u or in the
     * segment range.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    bool is_prime(const uint x) const
    {
        assert(x <= sieve_u or segment_l <= x and x <= segment_u);
        if(x <= sieve_u)
            return x <= 1? false : spf[x] == x;
        else
            return segment_spf[x - segment_l] == x;
    }

    /**
     * Returns the smallest prime factor of x.
     *
     * Note: x must be <= sieve_u or in the
     * precomputed segment range.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    uint smallest_prime_factor(const uint x) const
    {
        assert(1 < x and (x <= sieve_u or segment_l <= x and x <= segment_u));
        return x <= sieve_u? spf[x] : segment_spf[x - segment_l];
    }

    /**
     * Returns the computed prime numbers <=
     * sieve_u.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     * Where n is the sieve upper bound.
     */
    vector<uint> prime_numbers() const
    {
        return primes;
    }

    /**
     * Returns the computed prime numbers in the
     * segment range.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     * Where n is the size of the segment range (i.e. segment_u - segment_l + 1).
     */
    vector<uint> segment_prime_numbers() const
    {
        return segment_primes;
    }

private:
    uint sieve_u; // sieve upper bound.
    vector<uint> spf, primes; // smallest prime factor and the primes <= sieve_u.
    uint segment_l = 0, segment_u = 0; // segment upper and lower bounds.
    vector<uint> segment_spf, segment_primes; // segment smallest prime factor and the primes in [segment_u, segment_lower].
};
