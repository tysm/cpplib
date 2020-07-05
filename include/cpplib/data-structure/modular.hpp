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
 * Note: if __uint128_t is not present, *
 * may cause overflow before applying % if
 * the multiplication result >= pow(2, 64).
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<uint MOD = M>
struct modular {
    static_assert(MOD > 0, "MOD must be greater than 0.");

    uint value = 0;

    template<typename T>
    modular(const T value)
    {
        if(value >= 0)
            this->value = ((uint)value < MOD? value : (uint)value%MOD);
        else{
            uint abs_value = (-(uint)value)%MOD;
            this->value = (abs_value == 0? 0 : MOD - abs_value);
        }
    }

    template<typename T>
    explicit operator T() const
    {
        return value;
    }

    modular operator-()
    {
        return modular(value == 0? 0 : MOD - value);
    }

    modular &operator+=(const modular &rhs)
    {
        if(rhs.value >= MOD - value)
            value = rhs.value - (MOD - value);
        else
            value += rhs.value;
        return *this;
    }

    modular &operator-=(const modular &rhs)
    {
        if(rhs.value > value)
            value = MOD - (rhs.value - value);
        else
            value -= rhs.value;
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
        assert(get<0>(aux) == 1); // a and MOD must be coprimes.
        return modular(get<1>(aux));
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

    friend ostream &operator<<(ostream &lhs, const modular &rhs)
    {
        return lhs << rhs.value;
    }
};

using mint = modular<>;
