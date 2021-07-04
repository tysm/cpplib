#pragma once
#include <cpplib/stdinc.hpp>

struct XorBasis
{
    int d = 32, cnt = 0;
    vector<int> basis;

    XorBasis() :
        basis(d) {}

    XorBasis(int d) :
        d(d), basis(d)
    {}

    void insert(int mask)
    {
        rep(i, 0, d)
        {
            if(!((mask >> i) & 1))
                continue;
            if(basis[i])
                mask ^= basis[i];
            else {
                cnt++;
                basis[i] = mask;
                break;
            }
        }
    }

    bool count(int mask) const
    {
        rep(i, 0, d)
        {
            if(!((mask >> i) & 1))
                continue;
            if(basis[i])
                mask ^= basis[i];
            else
                return false;
        }
        return true;
    }
};
