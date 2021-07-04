#pragma once
#include <cpplib/adt/circle.hpp>
#include <cpplib/adt/point.hpp>
#include <cpplib/adt/triangle.hpp>
#include <cpplib/stdinc.hpp>

// Smallest Enclosing Circle/Sphere - O(n).
template<typename T>
circle<double> see(vector<point<T> > points)
{
    circle<double> circ(point<double>(0, 0), 0);

    random_shuffle(all(points));
    for(int i = 0; i < points.size(); i++) {
        if(count(circ, points[i]))
            continue;
        circ = circle<double>(points[i], 0);
        for(int j = 0; j < i; j++) {
            if(count(circ, points[j]))
                continue;
            circ = circle<double>((points[i] + points[j]) * 0.5L, distance(points[i], points[j]) * 0.5L);
            for(int k = 0; k < j; k++) {
                if(count(circ, points[k]))
                    continue;
                auto c = triangle<T>(points[i], points[j], points[k]).circumcenter();
                circ = circle<double>(c, distance(c, points[k]));
            }
        }
    }
    return circ;
}
