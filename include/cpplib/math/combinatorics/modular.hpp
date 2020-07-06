#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/data-structure/modular.hpp>

/**
 * Modular Combinatorics.
 *
 * Provides modular combinatorial algorithms
 * such as C and factorials.
 *
 * Note: if __uint128_t is not present, *
 * may cause overflow in modular operations.
 *
 * Time Complexity: O(N).
 * Space Complexity: O(N).
 */
template<uint N, uint MOD = M>
class ModC
{
public:
    using mint = modular<MOD>;

    ModC()
    {
        _fact = range_factorial(N);
        _inv = range_inverse(N);
    }

    /**
     * Modular Combination.
     *
     * Returns C(n, k)%MOD.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    mint C(uint n, uint k)
    {
        assert(k <= n and n <= N);
        return fact(n)*inv(fact(k))*inv(fact(n - k));
    }

    /**
     * Modular Factorial.
     *
     * Returns n!%MOD.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    mint fact(const uint n)
    {
        assert(n <= N);
        return _fact[n];
    }

    /**
     * Modular Multiplicative Inverse.
     *
     * Returns the modular multiplicative inverse
     * of a with mod MOD.
     *
     * Note: this specific algorithm requires a
     * prime MOD value.
     *
     * Time Complexity: O((a <= N? 1 : log(a))).
     * Space Complexity: O(1).
     */
    mint inv(const mint &a)
    {
        assert(a.value > 0);
        return a.value <= N? _inv[a.value] : inverse(a);
    }

private:
    /**
     * Range Modular Factorial.
     *
     * Computes the factorial for each natural <=
     * n, mod MOD.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     */
    vector<mint> range_factorial(const uint n) const
    {
        vector<mint> fact(n + 1);
        fact[0] = 1;
        for(uint i = 1; i <= n; ++i)
            fact[i] = fact[i-1]*i;
        return fact;
    }

    /**
     * Range Modular Multiplicative Inverse.
     *
     * Computes the modular multiplicative
     * inverse for each positive integer <= n
     * with mod MOD.
     *
     * Note: this specific algorithm requires a
     * prime MOD value.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     */
    vector<mint> range_inverse(const mint &n) const
    {
        assert(n.value > 0);
        vector<mint> inv(n.value + 1);
        inv[1] = 1;
        for(uint i = 2; i <= n.value; ++i)
            inv[i] = -inv[MOD%i]*(MOD/i);
        return inv;
    }

    vector<mint> _inv, _fact;
};
