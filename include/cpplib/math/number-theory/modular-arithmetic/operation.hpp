#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/math/number-theory/euclid.hpp>

/**
 * Modulus.
 *
 * Computes the positive result of a%m.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T,
typename enable_if<is_integral<T>::value, uint>::type = 0>
uint mod(const T a, const uint m = M){
    assert(m > 0);
    if(a >= 0)
        return ((uint)a < m? a : (uint)a%m);
    uint abs_a = (-(uint)a)%m;
    return (abs_a == 0? 0 : m - abs_a);
}

/**
 * Modular Addition.
 *
 * Computes (a+b)%m.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T1, typename T2,
typename enable_if<is_integral<T1>::value and is_integral<T2>::value, uint>::type = 0>
uint modadd(const T1 a, const T2 b, const uint m = M){
    assert(m > 0);
    uint mod_a = mod(a, m), mod_b = mod(b, m);
    if(mod_b >= m - mod_a)
        return mod_b - (m - mod_a);
    return mod_a + mod_b;
}

/**
 * Modular Subtraction.
 *
 * Computes (a-b)%m.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T1, typename T2,
typename enable_if<is_integral<T1>::value and is_integral<T2>::value, uint>::type = 0>
uint modsub(const T1 a, const T2 b, const uint m = M){
    assert(m > 0);
    uint mod_a = mod(a, m), mod_b = mod(b, m);
    if(mod_b > mod_a)
        return m - (mod_b - mod_a);
    return mod_a - mod_b;
}

/**
 * Modular Multiplication.
 *
 * Computes a*b%m.
 *
 * Note: if __uint128_t is not present,
 * mod_a*mod_b may cause overflow before
 * applying % if the multiplication result
 * >= pow(2, 64).
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T1, typename T2,
typename enable_if<is_integral<T1>::value and is_integral<T2>::value, uint>::type = 0>
uint modmul(const T1 a, const T2 b, const uint m = M){
    assert(m > 0);
    uint mod_a = mod(a, m), mod_b = mod(b, m);
    #ifdef __SIZEOF_INT128__
        return (__uint128_t)mod_a*mod_b%m;
    #else
        return (uint64_t)mod_a*mod_b%m;
    #endif
}

/**
 * Modular Multiplicative Inverse.
 *
 * Computes the modular multiplicative
 * inverse of a with mod m.
 *
 * Time Complexity: O(log(mod(a, m))).
 * Space Complexity: O(1).
 */
template<typename T,
typename enable_if<is_integral<T>::value, uint>::type = 0>
uint modinv(const T a, const uint m = M){
    assert(m > 0);
    auto aux = extended_gcd(mod(a, m), m);
    assert(get<0>(aux) == 1); // mod(a, m) and m must be coprimes.
    return mod(get<1>(aux), m);
}

/**
 * Modular Division.
 *
 * Computes a/b%m.
 *
 * Time Complexity: O(log(mod(b, m))).
 * Space Complexity: O(1).
 */
template<typename T1, typename T2,
typename enable_if<is_integral<T1>::value and is_integral<T2>::value, uint>::type = 0>
uint moddiv(const T1 a, const T2 b, const uint m = M){
    assert(m > 0);
    return modmul(a, modinv(b, m), m);
}

/**
 * Modular Binary Exponentiation.
 *
 * Computes pow(b, e)%m.
 *
 * Time Complexity: O(log(e)).
 * Space Complexity: O(1).
 */
template<typename T,
typename enable_if<is_integral<T>::value, uint>::type = 0>
uint modexp(const T b, uint e, const uint m = M){
    assert(m > 0);
    uint mod_b = mod(b, m), res = 1;
    for(; e > 0; e >>= 1){
        if(e & 1)
            res = modmul(res, mod_b, m);
        mod_b = modmul(mod_b, mod_b, m);
    }
    return res;
}
