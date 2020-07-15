#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/data-structure/geometry/point.hpp>

template<typename T>
struct segment {
    point<T> a, b;

    segment(){}

    template<typename T1, typename T2>
    segment(const point<T1> &a, const point<T2> &b) :
        a(a), b(b) {}

    template<typename T1>
    segment(const segment<T1> &s) :
        a(s.a), b(s.b) {}

    // Not null segment check - O(1).
    explicit operator bool() const
    {
        return a != b;
    }

    // Point lies on segment check - O(1).
    template<typename T1>
    bool count(const point<T1> &p) const
    {
        if(!(*this))
            return p == a;
        auto pa = a - p, pb = b - p;
        return parallel(pa, pb) and pa*pb <= 0;
    }

    // Segment equal to - O(1).
    template<typename T1>
    friend bool operator==(const segment &lhs, const segment<T1> &rhs)
    {
        return tie(lhs.a, lhs.b) == tie(rhs.a, rhs.b) or tie(lhs.a, lhs.b) == tie(rhs.b, rhs.a);
    }

    // Segment not equal to - O(1).
    template<typename T1>
    friend bool operator!=(const segment &lhs, const segment<T1> &rhs)
    {
        return !(lhs == rhs);
    }

    // Segment coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const segment<T1> &r, const segment &s)
    {
        return coplanar(r.b - r.a, s.b - s.a, s.a - r.a);
    }

    // Segment parallelism check - O(1).
    template<typename T1>
    friend bool parallel(const segment<T1> &r, const segment &s)
    {
        return parallel(r.b - r.a, s.b - s.a);
    }

    // Segment concurrency check - O(1).
    template<typename T1>
    friend bool concurrent(const segment<T1> &r, const segment &s)
    {
        return coplanar(r, s) and !parallel(r, s);
    }

    // Segment orthogonality check - O(1).
    template<typename T1>
    friend bool orthogonal(const segment<T1> &r, const segment &s)
    {
        return perpendicular(r.b - r.a, s.b - s.a);
    }

    // Segment perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const segment<T1> &r, const segment &s)
    {
        return coplanar(r, s) and orthogonal(r, s);
    }

    // Segment intersection check - O(1).
    template<typename T1>
    friend bool intersect(const segment<T1> &r, const segment &s)
    {
        if(r.count(s.a) or r.count(s.b) or s.count(r.a) or s.count(r.b))
            return true; // covers r == s, degenerate cases and partial intersection.
        else if(concurrent(s, r)){ // actually (line) intersection code.
            auto rs = s.a - r.a, rv = r.b - r.a, sv = s.b - s.a;
            double k = sqrt((double)squared_norm(rs^sv)/squared_norm(rv^sv));
            auto p = r.a + k*orientation(rs, sv, rv^sv)*rv;
            return r.count(p) and s.count(p);
        }
        return false;
    }

    template<typename T1>
    friend segment<double> intersection(const segment<T1> &r, const segment &s)
    {
        assert(intersect(r, s));
        if(r == s or !r)
            return r;
        else if(!s)
            return s;
        else if(concurrent(s, r)){ // actually (line) intersection code.
            auto rs = s.a - r.a, rv = r.b - r.a, sv = s.b - s.a;
            double k = sqrt((double)squared_norm(rs^sv)/squared_norm(rv^sv));
            auto p = r.a + k*orientation(rs, sv, rv^sv)*rv;
            return {p, p};
        }
        return {s.count(r.a)? r.a : r.b, r.count(s.a)? s.a : s.b};
    }

    // Point-segment distance - O(1).
    template<typename T1>
    friend double distance(const point<T1> &p, const segment &s)
    {
        auto ab = s.b - s.a, ap = p - s.a, bp = p - s.b;
        if(ap*ab <= 0)
            return distance(p, s.a);
        else if(bp*ab >= 0)
            return distance(p, s.b);
        return sqrt((double)squared_norm(ap^ab)/squared_norm(ab)); // same as distance(p, line(s.a, ab)).
    }

    // Closest point in segment - O(1).
    template<typename T1>
    friend point<double> closest(const point<T1> &p, const segment &s)
    {
        auto ab = s.b - s.a, ap = p - s.a, bp = p - s.b;
        if(ap*ab <= 0)
            return s.a;
        else if(bp*ab >= 0)
            return s.b;
        return point<double>(s.a) + ab*((double)(ap*ab)/squared_norm(ab)); // same as projection(p, line(s.a, ab)).
    }

    // String conversion - O(1).
    friend string to_string(const segment &s)
    {
        return '[' + to_string(s.a) + ' ' + to_string(s.b) + ']';
    }

    // Output - O(1).
    friend ostream &operator<<(ostream &lhs, const segment &rhs)
    {
        return lhs << to_string(rhs);
    }
};
