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

    template<typename T1>
    line(const line<T1> &l) :
        p(l.p), v(l.v) {}

    // Not null line check - O(1).
    explicit operator bool() const
    {
        return (bool)v;
    }

    // Point on line - O(1).
    template<typename T1,
    typename enable_if<is_arithmetic<T1>::value, uint>::type = 0>
    auto at(const T1 k) const -> point<typename common_type<T, T1>::type>
    {
        return p + k*v;
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
        return coplanar(s.b - s.a, l.v, l.p - s.a);
    }

    // Line-line coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const line<T1> &r, const line &l)
    {
        return coplanar(r.v, l.v, l.p - r.p);
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

    // Segment-line orthogonality check - O(1).
    template<typename T1>
    friend bool orthogonal(const segment<T1> &s, const line &l)
    {
        return perpendicular(s.b - s.a, l.v);
    }

    // Line-line orthogonality check - O(1).
    template<typename T1>
    friend bool orthogonal(const line<T1> &r, const line &l)
    {
        return perpendicular(r.v, l.v);
    }

    // Segment-line perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const segment<T1> &s, const line &l)
    {
        return coplanar(s, l) and orthogonal(s, l);
    }

    // Line-line perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const line<T1> &r, const line &l)
    {
        return coplanar(r, l) and orthogonal(r, l);
    }

    // Segment-line intersection check - O(1).
    template<typename T1>
    friend bool intersect(const segment<T1> &s, const line &l)
    {
        line<T1> r = {s.a, s.b - s.a};
        return r == l or (!s and l.count(s.a) or !l and s.count(l.p)) or (concurrent(r, l) and s.count(intersection(r, l).p));
    }

    // Line-line intersection check - O(1).
    template<typename T1>
    friend bool intersect(const line<T1> &r, const line &l)
    {
        return r == l or (!r and l.count(r.p) or !l and r.count(l.p)) or concurrent(r, l);
    }

    // Segment-line intersection - O(1).
    template<typename T1>
    friend segment<double> intersection(const segment<T1> &s, const line &l)
    {
        assert(intersect(s, l));
        line<T1> r = {s.a, s.b - s.a};
        if(r == l or !s)
            return s;
        else if(!l)
            return {l.p, l.p};
        auto aux = intersection(r, l);
        return {aux.p, aux.p};
    }

    // Line-line intersection - O(1).
    template<typename T1>
    friend line<double> intersection(const line<T1> &r, const line &l)
    {
        assert(intersect(r, l));
        if(r == l or !r)
            return r;
        else if(!l)
            return l;
        return {r.at(sqrt((double)squared_norm((l.p - r.p)^r.v)/squared_norm(l.v^r.v))), point<double>()};
    }

    // Point-line distance - O(1).
    template<typename T1>
    friend double distance(const point<T1> &p, const line &l)
    {
        return !l? distance(l.p, p) : sqrt((double)squared_norm((p - l.p)^l.v)/squared_norm(l.v));
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
