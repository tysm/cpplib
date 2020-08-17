#pragma once
#include <cpplib/adt/line.hpp>
#include <cpplib/adt/point.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
struct segment
{
    point<T> a, b;

    segment() {}

    template<typename T1, typename T2>
    segment(const point<T1> &a, const point<T2> &b) :
        a(a), b(b)
    {}

    template<typename T1>
    segment(const segment<T1> &s) :
        a(s.a), b(s.b)
    {}

    // Degenerate segment check - O(1).
    bool is_degenerate() const
    {
        return a == b;
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

    // Point lies on segment check - O(1).
    template<typename T1>
    friend bool count(const segment &s, const point<T1> &p)
    {
        if(s.is_degenerate())
            return p == s.a;
        auto pa = s.a - p, pb = s.b - p;
        return parallel(pa, pb) and pa * pb < EPS;
    }

    // Segment lies on segment check - O(1).
    template<typename T1>
    friend bool count(const segment &s, const segment<T1> &r)
    {
        return count(s, r.a) and count(s, r.b);
    }

    // Segment lies on line check - O(1).
    template<typename T1>
    friend bool count(const line<T1> &l, const segment &s)
    {
        return count(l, s.a) and count(l, s.b);
    }

    // Segment-segment coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const segment<T1> &r, const segment &s)
    {
        return coplanar(r.b - r.a, s.b - s.a, s.a - r.a);
    }

    // Segment-line coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const segment &s, const line<T1> &l)
    {
        return coplanar(s.b - s.a, l.v, l.p - s.a);
    }

    // Segment-segment parallelism check - O(1).
    template<typename T1>
    friend bool parallel(const segment<T1> &r, const segment &s)
    {
        return parallel(r.b - r.a, s.b - s.a);
    }

    // Segment-line parallelism check - O(1).
    template<typename T1>
    friend bool parallel(const segment &s, const line<T1> &l)
    {
        return parallel(s.b - s.a, l.v);
    }

    // Segment-segment concurrency check - O(1).
    template<typename T1>
    friend bool concurrent(const segment<T1> &r, const segment &s)
    {
        return coplanar(r, s) and !parallel(r, s);
    }

    // Segment-line concurrency check - O(1).
    template<typename T1>
    friend bool concurrent(const segment &s, const line<T1> &l)
    {
        return coplanar(s, l) and !parallel(s, l);
    }

    // Segment-segment orthogonality check - O(1).
    template<typename T1>
    friend bool orthogonal(const segment<T1> &r, const segment &s)
    {
        return perpendicular(r.b - r.a, s.b - s.a);
    }

    // Segment-line orthogonality check - O(1).
    template<typename T1>
    friend bool orthogonal(const segment &s, const line<T1> &l)
    {
        return perpendicular(s.b - s.a, l.v);
    }

    // Segment-segment perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const segment<T1> &r, const segment &s)
    {
        return coplanar(r, s) and orthogonal(r, s);
    }

    // Segment-line perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const segment &s, const line<T1> &l)
    {
        return coplanar(s, l) and orthogonal(s, l);
    }

    // Segment-segment intersection check - O(1).
    template<typename T1>
    friend bool intersect(const segment<T1> &r, const segment &s)
    {
        if(count(r, s.a) or count(r, s.b) or count(s, r.a) or count(s, r.b))
            return true;  // covers r == s, degenerate cases and partial intersection.
        line<T> l = {s.a, s.b - s.a};
        return intersect(r, l) and count(s, intersection(r, l).a);
    }

    // Segment-line intersection check - O(1).
    template<typename T1>
    friend bool intersect(const segment &s, const line<T1> &l)
    {
        line<T> r = {s.a, s.b - s.a};
        if(r == l)
            return true;
        else if(s.is_degenerate() and count(l, s.a))
            return true;
        else if(l.is_degenerate() and count(s, l.p))
            return true;
        return concurrent(r, l) and count(s, intersection(r, l).p);
    }

    // Segment-segment intersection - O(1).
    template<typename T1>
    friend segment<double> intersection(const segment<T1> &r, const segment &s)
    {
        assert(intersect(r, s));
        if(r == s or r.is_degenerate() or count(s, r))
            return r;
        else if(s.is_degenerate() or count(r, s))
            return s;
        else if(concurrent(r, s))
            return intersection(r, line<T>(s.a, s.b - s.a));
        return {count(s, r.a) ? r.a : r.b, count(r, s.a) ? s.a : s.b};
    }

    // Segment-line intersection - O(1).
    template<typename T1>
    friend segment<double> intersection(const segment &s, const line<T1> &l)
    {
        assert(intersect(s, l));
        line<T> r = {s.a, s.b - s.a};
        if(r == l or s.is_degenerate())
            return s;
        else if(l.is_degenerate())
            return {l.p, l.p};
        auto aux = intersection(r, l);
        return {aux.p, aux.p};
    }

    // Point-segment distance - O(1).
    template<typename T1>
    friend double distance(const point<T1> &p, const segment &s)
    {
        auto ab = s.b - s.a, ap = p - s.a, bp = p - s.b;
        if(ap * ab < EPS)
            return distance(p, s.a);
        else if(bp * ab > -EPS)
            return distance(p, s.b);
        return distance(p, line<T>(s.a, ab));
    }

    // Closest point in segment - O(1).
    template<typename T1>
    friend point<double> closest(const point<T1> &p, const segment &s)
    {
        auto ab = s.b - s.a, ap = p - s.a, bp = p - s.b;
        if(ap * ab < EPS)
            return s.a;
        else if(bp * ab > -EPS)
            return s.b;
        return projection(p, line<T>(s.a, ab));
    }

    // Segment projection onto line - O(1).
    template<typename T1>
    friend segment<double> projection(const segment &s, const line<T1> &l)
    {
        return {projection(s.a, l), projection(s.b, l)};
    }

    // Segment reflection over line - O(1).
    template<typename T1>
    friend segment<double> reflection(const segment &s, const line<T1> &l)
    {
        return {reflection(s.a, l), reflection(s.b, l)};
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
