#pragma once
#include <cpplib/stdinc.hpp>

template<typename T, typename T1>
bool eq(const T &a, const T1 &b)
{
    return abs(a - b) < EPS;
}

template<typename T, typename T1>
bool neq(const T &a, const T1 &b)
{
    return !eq(a, b);
}

template<typename T, typename T1>
bool ls(const T &a, const T1 &b)
{
    return a <= b - EPS;
}  // same as: a < b and notEqual(a, b).

template<typename T, typename T1>
bool gr(const T &a, const T1 &b)
{
    return ls(b, a);
}

template<typename T, typename T1>
bool ls_eq(const T &a, const T1 &b)
{
    return !gr(a, b);
}

template<typename T, typename T1>
bool gr_eq(const T &a, const T1 &b)
{
    return !ls(a, b);
}
