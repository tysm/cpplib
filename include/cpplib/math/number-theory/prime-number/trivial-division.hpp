#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Trivial Division.
 *
 * Returns true when n is prime, false
 * otherwise.
 *
 * Time Complexity: O(sqrt(n)).
 * Space Complexity: O(1).
 */
bool isprime(const int n){
    for(int i=2; i*i<=n; ++i){
        if(n%i == 0)
            return false;
    }
    return true;
}
