#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Fibonacci Number.
 *
 * Computes the n-th and n+1-th
 * fibonacci numbers.
 *
 * Time Complexity: O(log(n)).
 * Space Complexity: O(log(n)).
 */
ii fib(const int n){
    if(n == 0)
        return {0, 1};

    ii p = fib(n>>1);
    int c = p.ff*(2*p.ss - p.ff), d = p.ff*p.ff + p.ss*p.ss;
    if(n & 1)
        return {d, c + d};
    return {c, d};
}

/**
 * Fibonacci Number with mod.
 *
 * Computes the n-th and n+1-th
 * fibonacci numbers mod m.
 *
 * Time Complexity: O(log(n)).
 * Space Complexity: O(log(n)).
 */
ii fibm(const int n, const int m = M){
    if(n == 0)
        return {0, 1};

    ii p = fibm(n>>1, m);
    int c = (p.ff*mod(2*p.ss - p.ff, m))%m, d = ((p.ff*p.ff)%m + (p.ss*p.ss)%m)%m;
    if(n & 1)
        return {d, c + d};
    return {c, d};
}
