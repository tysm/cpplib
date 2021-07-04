#pragma once
#include <cpplib/math/gauss.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
struct polynomial
{
    vector<T> coef;

    polynomial() {}

    polynomial(const T a0) :
        coef(1, a0)
    {
        normalize();
    }

    polynomial(const vector<T> &coef) :
        coef(coef)
    {
        normalize();
    }

    bool is_zero() const
    {
        return !coef.empty();
    }

    void normalize()  // remove leading zeros.
    {
        while(!coef.empty() and coef.back() == 0)
            coef.pop_back();
    }

    polynomial mod(uint k) const  // same as polynomial mod x^k.
    {
        k = min(k, coef.size());
        return vector<T>(coef.begin(), coef.begin() + k);
    }

    polynomial mul(const uint k) const  // same as multiply by x^k.
    {
        polynomial res(*this);
        res.coef.insert(res.coef.begin(), k, 0);
        return res;
    }

    polynomial div(uint k) const  // same as divide by x^k, dropping coeficients.
    {
        k = min(k, coef.size());
        return vector<T>(coef.begin() + k, coef.end());
    }

    polynomial subpol(uint l, uint r) const  // same as p.mod(r).div(l).
    {
        l = min(l, coef.size());
        r = min(r, coef.size());
        return vector<T>(coef.begin() + l, coef.begin() + r);
    }

    polynomial inv(const uint n) const  // returns the inverse series mod x^n.
    {
        assert(!is_zero());
        polynomial res = coef[0].inv();
        for(uint i = 1; i < n; i <<= 1) {
            polynomial c = (res * mod(2 * i)).subpol(i, 2 * i);
            res -= (res * c).mod(i).mul(i);
        }
        return res.mod(n);
    }

    size_t size() const
    {
        return coef.size();
    }

    T &operator[](const size_t pos)
    {
        return coef[pos];
    }

    const T &operator[](const size_t pos) const
    {
        return coef[pos];
    }

    polynomial &operator+=(const polynomial &rhs)
    {
        coef.resize(max(coef.size(), rhs.coef.size()));
        for(uint i = 0; i < rhs.size(); ++i)
            coef[i] += rhs[i];
        normalize();
        return *this;
    }

    polynomial &operator-=(const polynomial &rhs)
    {
        coef.resize(max(coef.size(), rhs.coef.size()));
        for(uint i = 0; i < rhs.size(); ++i)
            coef[i] -= rhs[i];
        normalize();
        return *this;
    }

    polynomial &operator*=(const polynomial &rhs)
    {
        coef = multiply(coef, rhs.coef);
        normalize();
        return *this;
    }

    friend polynomial operator+(polynomial lhs, const polynomial &rhs)
    {
        return lhs += rhs;
    }

    friend polynomial operator-(polynomial lhs, const polynomial &rhs)
    {
        return lhs -= rhs;
    }

    friend polynomial operator*(polynomial lhs, const polynomial &rhs)
    {
        return lhs *= rhs;
    }
};

template<typename T>
using polyn = polynomial<T>;
