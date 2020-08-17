#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/utility/random.hpp>

const array<uint, 3> mods({(uint)1e9 + 7, 998244353, (uint)randint(1e8, 1e9)});

struct hashint
{
    array<uint, 3> values;

    hashint() :
        values({0, 1, 0}) {}

    template<typename T>
    hashint(const T value)
    {
        for(int i = 0; i < 3; ++i)
            values[i] = (value % mods[i] + mods[i]) % mods[i];
    }

    hashint &operator+=(const hashint &rhs)
    {
        values[0] = (values[0] + rhs.values[0]) % mods[0];
        values[1] = ((uint64_t)values[1] * rhs.values[1]) % mods[1];
        values[2] = (values[2] + rhs.values[2]) % mods[2];
        return *this;
    }

    friend hashint operator+(hashint lhs, const hashint &rhs)
    {
        return lhs += rhs;
    }

    friend bool operator==(const hashint &lhs, const hashint &rhs)
    {
        for(int i = 0; i < 3; ++i) {
            if(lhs.values[i] != rhs.values[i])
                return false;
        }
        return true;
    }

    friend bool operator!=(const hashint &lhs, const hashint &rhs)
    {
        return !(lhs == rhs);
    }
};

using hint = hashint;
