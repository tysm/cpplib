#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Wheel Prime Factorization.
 *
 * Computes the prime factorization of x.
 *
 * Time Complexity: O(sqrt(x)).
 * Space Complexity: O(log(x)).
 */
vector<pair<uint, uint> > factorization(uint x){
    assert(x > 0);
    vector<pair<uint, uint> > factors;
    for(uint p : {2, 3, 5}){
        while(x%p == 0){
            if(factors.empty() or factors.back().first != p)
                factors.emplace_back(p, 1);
            else
                factors.back().second++;
            x /= p;
        }
    }
    vector<uint> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    for(uint p = 7, i = 0; p*p <= x; p += increments[i++], i %= 8){
        while(x%p == 0){
            if(factors.empty() or factors.back().first != p)
                factors.emplace_back(p, 1);
            else
                factors.back().second++;
            x /= p;
        }
    }
    if(x > 1) // x is prime.
        factors.emplace_back(x, 1);
    return factors;
}
