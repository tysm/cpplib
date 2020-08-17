#pragma once
#include <cpplib/adt/point.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
tuple<point<double>, double> see(const vector<point<T> > &points, uint iterations = 30000)
{
    uint n = points.size();

    point<double> c;
    for(uint i = 0; i < n; ++i)
        c += points[i];
    c /= n;

    for(double p = 0.1; iterations; p *= 0.999, --iterations) {
        uint f = n;
        double r = 0;
        for(uint i = 0; i < n; ++i) {
            double d = squared_norm(points[i] - c);
            if(d > r) {
                f = i;
                r = d;
            }
        }
        if(f == n)
            break;
        c += (points[f] - c) * p;
    }

    double r = 0;
    for(uint i = 0; i < n; ++i)
        r = max(r, squared_norm(points[i] - c));
    return {c, sqrt(r)};
}
