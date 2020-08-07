#pragma once
#include <cpplib/math/modoperation.hpp>
#include <cpplib/math/modprogression.hpp>
#include <cpplib/math/wheel.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Sum of Divisors.
 *
 * Computes the sum of divisors of x, mod m.
 *
 * Time Complexity: O(sqrt(x) + log(x)*(log(x) + log(m))).
 * Space Complexity: O(log(x)).
 */
uint modsum_divisors(const uint x, const uint m = M) {
    assert(x > 0 and m > 0);
    uint res = 1;
    for(auto f: factorization(x))
        res = modmul(res, modsum_gp(1, f.first, f.second + 1, m), m);
    return res;
}

/**
 * Range Sum of Divisors.
 *
 * Computes the sum of the sum of divisors
 * for each integer in [1, n], mod M.
 *
 * Time Complexity: O(sqrt(n)).
 * Space Complexity: O(1).
 */
uint modrange_sum_divisors(const uint n, const uint m = M) {
    assert(n > 0 and m > 0);
    uint ans = 0;
    for(uint d = 1; d * d <= n; ++d) {
        uint l = n / (d + 1) + 1, r = n / d;
        ans = modadd(ans, modmul(d, modsum_ap(l, 1, r - l + 1, m), m), m);
        if(d != n / d)
            ans = modadd(ans, modmul(n / d, d, m), m);
    }
    return ans;
}

/**
 * Range Sum of Divisors.
 *
 * Computes the sum of the sum of divisors
 * for each integer in [l, r], mod M.
 *
 * Time Complexity: O(sqrt(l) + sqrt(r)).
 * Space Complexity: O(1).
 */
uint modrange_sum_divisors(const uint l, const uint r, const uint m) {
    assert(l > 0 and l <= r and m > 0);
    int ans = modrange_sum_divisors(r, m);
    if(l > 1)
        ans = modsub(ans, modrange_sum_divisors(l - 1, m), m);
    return ans;
}
