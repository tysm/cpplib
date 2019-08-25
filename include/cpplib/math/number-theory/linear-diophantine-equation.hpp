#pragma once
#include <cpplib/header>

/**
 * Linear Diophantine Equation Solution.
 *
 * Returns the roots of the given LDE.
 *
 * Note: it doesn't check if "a*x + b*y = c"
 * is a LDE, i.e. if gcd(abs(a), abs(b)) divides c.
 *
 * Time Complexity: O(log(min(a, b))).
 */
ii lde(int a, int b, int c){
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
