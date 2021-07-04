#pragma once
#include <cpplib/adt/point.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
static int quad(const point<T> &p)
{
    if(p.x >= 0)
        return p.y >= 0 ? 1 : 4;
    else
        return p.y >= 0 ? 2 : 3;
    assert(false);
}

template<typename T>
static bool cmp(const point<T> &i, const point<T> &j, const point<T> &org)
{
    auto oi = i - org, oj = j - org;
    int qi = quad(oi), qj = quad(oj);
    if(qi < qj)
        return true;
    else if(qi == qj) {
        int o = get<2>(orientation(oi, oj));
        if(o > 0)
            return true;
        else if(o == 0)
            return squared_norm(point<T>(oi.x, oi.y)) <= squared_norm(point<T>(oj.x, oj.y)) - EPS;
    }
    return false;
}

template<typename T>
void polar_sort(vector<point<T> > &points, const point<T> &org = O)
{
    sort(all(points), [org](const point<T> &i, const point<T> &j) { return cmp(i, j, org); });
}
