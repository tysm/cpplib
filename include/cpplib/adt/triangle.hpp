#pragma once
#include <cpplib/adt/point.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
struct triangle
{
    point<T> a, b, c;

    triangle(const point<T> &a, const point<T> &b, const point<T> &c) :
        a(a), b(b), c(c) {}

    double area() const
    {
        return abs(((b - a) ^ (c - b)).z) * 0.5L;
    }

    // Barycenter - O(1).
    point<double> barycenter(double A, double B, double C) const
    {
        return (a * A + b * B + c * C) / (A + B + C);
    }

    // Geometric center of mass - O(1).
    point<double> centroid() const
    {
        return barycenter(1, 1, 1);
    }

    // Intersection of perpendicular bisectors - O(1).
    point<double> circumcenter() const
    {
        double A = squared_norm(c - b), B = squared_norm(a - c), C = squared_norm(b - a);
        return barycenter(A * (B + C - A), B * (C + A - B), C * (A + B - C));
    }

    // Intersection of internal angle bisectors - O(1).
    point<double> incenter() const
    {
        double A = distance(b, c), B = distance(a, c), C = distance(a, b);
        return barycenter(A, B, C);
    }

    // Intersection of external angle bisectors - O(1).
    point<double> excenter(int op = -1) const
    {
        double A = distance(b, c), B = distance(a, c), C = distance(a, b);
        if(op < 0)
            return barycenter(-A, B, C);
        else if(op == 0)
            return barycenter(A, -B, C);
        return barycenter(A, B, -C);
    }

    // Intersection of altitudes - O(1).
    point<double> orthocenter() const
    {
        double A = squared_norm(c - b), B = squared_norm(a - c), C = squared_norm(b - a);
        return barycenter((A + B - C) * (C + A - B), (B + C - A) * (A + B - C), (C + A - B) * (B + C - A));
    }

    // Smallest distance from incenter to any side - O(1).
    double inradius() const
    {
        double A = distance(b, c), B = distance(a, c), C = distance(a, b);
        double S = (A + B + C) / 2.0L;
        return area() / S;
    }

    template<typename T1>
    friend bool count(const triangle &t, const point<T1> &p)
    {
        auto s1 = abs(((t.b - t.a) ^ (t.c - t.b)).z);
        auto s2 = abs(((t.b - p) ^ (t.c - t.b)).z) + abs(((t.c - p) ^ (t.a - t.c)).z) + abs(((t.a - p) ^ (t.b - t.a)).z);
        return abs(s1 - s2) < EPS;
    }
};
