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

    // Segment equivalent to - O(1).
    template<typename T1>
    friend bool operator==(const segment &lhs, const segment<T1> &rhs)
    {
        return tie(lhs.a, lhs.b) == tie(rhs.a, rhs.b);
    }

    // Segment not equivalent to - O(1).
    template<typename T1>
    friend bool operator!=(const segment &lhs, const segment<T1> &rhs)
    {
        return !(lhs == rhs);
    }

    // Segment coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const segment<T1> &r, const segment &s)
    {
        return parallel(r, s) or parallel(s.a - r.a, r.b - r.a + s.b - s.a);
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

    // Point-segment distance - O(1).
    template<typename T1>
    friend double distance(const point<T1> &p, const segment &s)
    {
        auto ab = s.b - s.a, ap = p - s.a, bp = p - s.b;
        if(ap*ab <= 0)
            return distance(p, s.a);
        else if(bp*ab >= 0)
            return distance(p, s.b);
        return norm(ap^ab)/norm(ab); // same as distance(p, line(s.a, ab)).
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

    // Segment string conversion - O(1).
    friend string to_string(const segment &s)
    {
        return '[' + to_string(s.a) + ' ' + to_string(s.b) + ']';
    }

    // Segment output - O(1).
    friend ostream &operator<<(ostream &lhs, const segment &rhs)
    {
        return lhs << to_string(rhs);
    }
};
