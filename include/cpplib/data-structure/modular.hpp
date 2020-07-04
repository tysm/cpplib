#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/euclid.hpp>

/**
 * Modular.
 *
 * Provides modular operations such as +, -,
 * *, /, multiplicative inverse and
 * binary exponentiation.
 *
 * Note: MOD must be positive.
 *
 * Note: if __uint128_t is not present, + and
 * * may cause overflow before applying % if
 * the operation result >= pow(2, 64).
 *
 * Note: if T is unsigned, then - may cause
 * underflow before applying % if rhs > lhs.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T, T MOD = M>
struct modular {
    T value;

    modular(T value = 0)
    {
        this->value = value%MOD;
        if(this->value < 0)
            this->value += MOD;
    }

    explicit operator T() const
    {
        return value;
    }

    modular &operator+=(const modular &rhs)
    {
        #ifdef __SIZEOF_INT128__
            value = ((__uint128_t)value + rhs.value)%MOD;
        #else
            value = ((uint64_t)value + rhs.value)%MOD;
        #endif
        return *this;
    }

    modular &operator-=(const modular &rhs)
    {
        if((value -= rhs.value) < 0)
            value += MOD;
        return *this;
    }

    modular &operator*=(const modular &rhs)
    {
        #ifdef __SIZEOF_INT128__
            value = (__uint128_t)value*rhs.value%MOD;
        #else
            value = (uint64_t)value*rhs.value%MOD;
        #endif
        return *this;
    }

    modular &operator/=(const modular &rhs)
    {
        return *this *= inverse(rhs);
    }

    /**
     * Modular Binary Exponentiation.
     *
     * Computes pow(b, e)%MOD.
     *
     * Time Complexity: O(log(e)).
     * Space Complexity: O(1).
     */
    friend modular exp(modular b, uint e)
    {
        modular res = 1;
        for(; e > 0; e >>= 1){
            if(e & 1)
                res *= b;
            b *= b;
        }
        return res;
    }

    /**
     * Modular Multiplicative Inverse.
     *
     * Computes the modular multiplicative
     * inverse of a with mod MOD.
     *
     * Time Complexity: O(log(a)).
     * Space Complexity: O(1).
     */
    friend modular inverse(const modular &a)
    {
        auto aux = extended_gcd(a.value, MOD);
        assert(get<0>(aux) == 1); // a and M must be coprimes.
        return modular(get<1>(aux));
    }

    /**
     * Range Modular Multiplicative Inverse.
     *
     * Computes the modular multiplicative
     * inverse for each natural <= n with mod MOD.
     *
     * Time Complexity: O(n).
     * Space Complexity: O(n).
     */
    friend vector<T> range_inverse(const modular &n)
    {
        vector<T> inv(n.value + 1);
        inv[1] = 1;
        for(T i=2; i<=n.value; ++i)
            inv[i] = (MOD - (MOD/i)*inv[MOD%i]%MOD)%MOD;
        return inv;
    }

    friend modular operator+(modular lhs, const modular &rhs)
    {
        return lhs += rhs;
    }

    friend modular operator-(modular lhs, const modular &rhs)
    {
        return lhs -= rhs;
    }

    friend modular operator*(modular lhs, const modular &rhs)
    {
        return lhs *= rhs;
    }

    friend modular operator/(modular lhs, const modular &rhs)
    {
        return lhs /= rhs;
    }

    friend bool operator==(const modular &lhs, const modular &rhs)
    {
        return lhs.value == rhs.value;
    }

    friend bool operator!=(const modular &lhs, const modular &rhs)
    {
        return lhs.value != rhs.value;
    }

    friend istream &operator>>(istream &lhs, modular &rhs)
    {
        T value;
        lhs >> value;
        rhs = value;
    }

    friend ostream &operator<<(ostream &lhs, const modular &rhs)
    {
        return lhs << rhs.value;
    }
};

using mint = modular<int>;
