#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/data-structure/geometry/point.hpp>
#include <cpplib/data-structure/geometry/segment.hpp>

template<typename T>
struct line {
    point<T> p, v;

    line(){}

    template<typename T1, typename T2>
    line(const point<T1> &p, const point<T2> &v) :
        p(p), v(v) {}

    // Not null line check - O(1).
    explicit operator bool() const
    {
        return (bool)v;
    }

    // Point lies on line check - O(1).
    template<typename T1>
    bool count(const point<T1> &q) const
    {
        return !(*this)? q == p : parallel((q - p), v);
    }

    // Segment lies on line check - O(1).
    template<typename T1>
    bool count(const segment<T1> &s) const
    {
        return count(s.a) and count(s.b);
    }

    // Line equivalent to - O(1).
    template<typename T1>
    friend bool operator==(const line &lhs, const line<T1> &rhs)
    {
        if(!lhs and !rhs)
            return lhs.p == rhs.p;
        else if(lhs and rhs)
            return parallel(lhs, rhs) and lhs.count(rhs.p);
        return false;
    }

    // Line not equivalent to - O(1).
    template<typename T1>
    friend bool operator!=(const line &lhs, const line<T1> &rhs)
    {
        return !(lhs == rhs);
    }

    // Segment-line coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const segment<T1> &s, const line &l)
    {
        return parallel(s, l) or parallel(l.p - s.a, s.b - s.a + l.v);
    }

    // Line-line coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const line<T1> &r, const line &l)
    {
        return parallel(r, l) or parallel(l.p - r.p, r.v + l.v);
    }

    // Segment-line parallelism check - O(1).
    template<typename T1>
    friend bool parallel(const segment<T1> &s, const line &l)
    {
        return parallel(s.b - s.a, l.v);
    }

    // Line-line parallelism check - O(1).
    template<typename T1>
    friend bool parallel(const line<T1> &r, const line &l)
    {
        return parallel(r.v, l.v);
    }

    // Segment-line concurrency check - O(1).
    template<typename T1>
    friend bool concurrent(const segment<T1> &s, const line &l)
    {
        return coplanar(s, l) and !parallel(s, l);
    }

    // Line-line concurrency check - O(1).
    template<typename T1>
    friend bool concurrent(const line<T1> &r, const line &l)
    {
        return coplanar(r, l) and !parallel(r, l);
    }

    // Point-line distance - O(1).
    template<typename T1>
    friend double distance(const point<T1> &p, const line &l)
    {
        return !l? distance(l.p, p) : norm((p - l.p)^l.v)/norm(l.v);
    }

    // Point projection onto line - O(1).
    template<typename T1>
    friend point<double> projection(const point<T1> &p, const line &l)
    {
        point<double> res = l.p;
        if(l)
            res += l.v*((double)((p - l.p)*l.v)/squared_norm(l.v));
        return res;
    }

    // Segment projection onto line - O(1).
    template<typename T1>
    friend segment<double> projection(const segment<T1> &s, const line &l)
    {
        return {projection(s.a, l), projection(s.b, l)};
    }

    // Point reflection over line - O(1).
    template<typename T1>
    friend point<double> reflection(const point<T1> &p, const line &l)
    {
        return 2*projection(p, l) - p;
    }

    // Segment reflection over line - O(1).
    template<typename T1>
    friend segment<double> reflection(const segment<T1> &s, const line &l)
    {
        return {reflection(s.a, l), reflection(s.b, l)};
    }

    // Line reflection over line - O(1).
    template<typename T1>
    friend line<double> reflection(const line<T1> &r, const line &l)
    {
        auto s = reflection(segment<T1>(r.p, r.p + r.v), l);
        return {s.a, s.b - s.a};
    }

    // Line string conversion - O(1).
    friend string to_string(const line &l)
    {
        return '[' + to_string(l.p) + ' ' + to_string(l.v) + ']';
    }

    // Line output - O(1).
    friend ostream &operator<<(ostream &lhs, const line &rhs)
    {
        return lhs << to_string(rhs);
    }
};
