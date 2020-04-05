#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Linear Diophantine Equation Solution.
 *
 * Returns the roots of the given LDE.
 *
 * Note: it doesn't check if
 * "a*x + b*y = c" is a LDE, i.e. if
 * gcd(abs(a), abs(b)) divides c.
 *
 * Time Complexity: O(log(min(a, b))).
 * Space Complexity: O(log(min(a, b))).
 */
ii lde(const int a, const int b, const int c){
    pair<int, ii> _gcd = gcd(abs(a), abs(b));

    int x = _gcd.ss.ff, y = _gcd.ss.ss, g = _gcd.ff;
    x *= c/g;
    y *= c/g;

    if(a < 0)
        x = -x;
    if(b < 0)
        y = -y;
    return {x, y};
}
