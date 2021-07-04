#pragma once
#include <cpplib/stdinc.hpp>

struct Line
{
    mutable int64_t k, m, p;
    bool operator<(const Line &o) const { return k < o.k; }
    bool operator<(int64_t x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<> >
{
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const int64_t inf = LLONG_MAX;
    int64_t div(int64_t a, int64_t b)
    {  // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y)
    {
        if(y == end())
            return x->p = inf, 0;
        if(x->k == y->k)
            x->p = x->m > y->m ? inf : -inf;
        else
            x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(int64_t k, int64_t m)
    {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if(x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    int64_t query(int64_t x)
    {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};
