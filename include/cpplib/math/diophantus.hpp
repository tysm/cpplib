#pragma once
#include <cpplib/math/euclid.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Linear Diophantine Equation.
 *
 * Returns the roots of the given LDE.
 *
 * Note: a*x + b*y = c is LDE if, and
 * only if, gcd(a, b) divides c.
 *
 * Time Complexity: O(log(min(abs(a), abs(b)))).
 * Space Complexity: O(1).
 */
tuple<int, int> diophantine(const int a, const int b, const int c) {
    int g, x, y;
    tie(g, x, y) = extended_gcd(abs(a), abs(b));
    assert(c % g == 0);  // LDE condition.

    x *= c / g;
    y *= c / g;

    int k = min(abs(x / (b / g)), abs(y / (a / g)));
    if(abs(y) > abs(x)) {
        x += k * (b / g) * (y > 0 ? 1 : -1);
        y -= k * (a / g) * (y > 0 ? 1 : -1);
    }
    else {
        x -= k * (b / g) * (x > 0 ? 1 : -1);
        y += k * (a / g) * (x > 0 ? 1 : -1);
    }

    if(a < 0)
        x = -x;
    if(b < 0)
        y = -y;
    return make_tuple(x, y);
}

/**
 * Linear Diophantine Equation.
 *
 * Returns the roots of the given LDE.
 *
 * Note: a1*x1 + ... + an*xn = c is LDE
 * if, and only if, gcd(a1, ..., an)
 * divides c.
 *
 * Time Complexity: O(n*log(a)).
 * Space Complexity: O(n).
 * Where n is the number of coefficients and a is the greatest among them.
 */
vector<int> diophantine(const vector<int> &values, int c) {
    int n = values.size();
    vector<int> g(n);
    g[n - 1] = abs(values[n - 1]);
    for(int i = n - 2; i >= 0; --i) {
        if(values[i] % g[i + 1] == 0)
            g[i] = g[i + 1];
        else
            g[i] = gcd(abs(values[i]), g[i + 1]);
    }
    assert(c % g[0] == 0);  // LDE condition.

    vector<int> ans(n);
    for(int i = 0; i < n; ++i) {
        if(i == n - 1)
            ans[i] = c / values[i];
        else if(g[i] != g[i + 1])
            ans[i] = get<0>(diophantine(values[i], g[i + 1], c));
        c -= values[i] * ans[i];
    }
    return ans;
}
