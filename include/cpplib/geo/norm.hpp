#pragma once
#include <cpplib/adt/point.hpp>
#include <cpplib/math/euclid.hpp>
#include <cpplib/stdinc.hpp>

point<int> normalize(point<int> p)
{
    if(p.x == 0)
        return {0, 1};
    if(p.y == 0)
        return {1, 0};
    int g = gcd(abs(p.x), abs(p.y));
    p /= g;
    if(p.y < 0)
        return -p;
    return p;
}
