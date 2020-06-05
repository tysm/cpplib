#pragma once
#include <cpplib/stdinc.hpp>

/**
 * Extended Euclidean GCD.
 *
 * Besides computing the GCD it also returns
 * the roots of a*x + b*y = gcd(a, b).
 *
 * Time Complexity: O(log(min(a, b))).
 */
pair<int, ii> egcd(const int a, const int b){
    if(a < 0 or b < 0)
        return egcd(abs(a), abs(b));
    if(a == 0)
        return {b, {0, 1}};
    pair<int, ii> res = egcd(b%a, a);
    int x1 = res.ss.ff, y1 = res.ss.ss;
    return {res.ff, {y1 - b/a*x1, x1}};
}

/**
 * Linear Diophantine Equation Solution.
 *
 * Returns the roots of the given LDE.
 *
 * Note: a*x + b*y = c is LDE if, and
 * only if, gcd(a, b) divides c.
 *
 * Time Complexity: O(log(min(a, b))).
 * Space Complexity: O(log(min(a, b))).
 */
ii lde(const int a, const int b, const int c){
    pair<int, ii> _gcd = egcd(a, b);
    int x = _gcd.ss.ff, y = _gcd.ss.ss, g = _gcd.ff;
    assert(c%g == 0); // LDE condition.

    x *= c/g;
    y *= c/g;

    int k = min(abs(x/(b/g)), abs(y/(a/g)));
    if(abs(y) > abs(x)){
        x += k*(b/g)*(y > 0? 1 : -1);
        y -= k*(a/g)*(y > 0? 1 : -1);
    }
    else{
        x -= k*(b/g)*(x > 0? 1 : -1);
        y += k*(a/g)*(x > 0? 1 : -1);
    }

    if(a < 0)
        x = -x;
    if(b < 0)
        y = -y;
    return {x, y};
}

/**
 * Linear Diophantine Equation Solution.
 *
 * Returns the roots of the given LDE.
 *
 * Note: a1*x1 + ... + an*xn = c is LDE
 * if, and only if, gcd(a1, ..., an)
 * divides c.
 *
 * Time Complexity: O(log(min(a, b))).
 * Space Complexity: O(log(min(a, b))).
 */
vi lde(const vi &values, int c){
    int n = values.size();
    vi g(n);
    g[n-1] = abs(values[n-1]);
    for(int i=n-2; i>=0; --i){
        if(values[i]%g[i+1] == 0)
            g[i] = g[i+1];
        else
            g[i] = gcd(values[i], g[i+1]);
    }
    assert(c%g[0] == 0); // LDE condition.

    vi ans(n);
    for(int i=0; i<n; ++i){
        if(i == n-1)
            ans[i] = c/values[i];
        else if(g[i] != g[i+1])
            ans[i] = lde(values[i], g[i+1], c).ff;
        c -= values[i]*ans[i];
    }
    return ans;
}
