#pragma once
#include <cpplib/header.hpp>

/**
 * Trivial Division.
 *
 * Returns true when n is prime,
 * false otherwise.
 *
 * Time Complexity: O(sqrt(n)).
 */
bool isprime(int n){
    for(int i=2; i*i<=n; ++i){
        if(n%i == 0)
            return false;
    }
    return true;
}
