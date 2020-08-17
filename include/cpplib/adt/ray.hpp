#pragma once
#include <cpplib/adt/line.hpp>
#include <cpplib/adt/point.hpp>
#include <cpplib/adt/segment.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
struct ray
{
    point<T> p, v;

    ray() {}

    template<typename T1, typename T2>
    ray(const point<T1> &p, const point<T2> &v) :
        p(p), v(v)
    {}

    template<typename T1>
    ray(const ray<T1> &r) :
        p(r.p), v(r.v)
    {}

    // Degenerate ray check - O(1).
    bool is_degenerate() const
    {
        return v.is_null();
    }

    // Point on ray - O(1).
    template<typename T1,
        typename enable_if<is_arithmetic<T1>::value, uint>::type = 0>
    auto at(const T1 k) const -> point<typename common_type<T, T1>::type>
    {
        assert(k > -EPS);
        return p + k * v;
    }

    // Ray equivalent to - O(1).
    template<typename T1>
    friend bool operator==(const ray &lhs, const ray<T1> &rhs)
    {
        if(lhs.p != rhs.p)
            return false;
        else if(lhs.is_degenerate() and rhs.is_degenerate())
            return true;
        else if(!lhs.is_degenerate() and !rhs.is_degenerate())
            return parallel(lhs, rhs) and lhs.v * rhs.v > -EPS;
        return false;
    }

    // Ray not equivalent to - O(1).
    template<typename T1>
    friend bool operator!=(const ray &lhs, const ray<T1> &rhs)
    {
        return !(lhs == rhs);
    }

    // Point lies on ray check - O(1).
    template<typename T1>
    friend bool count(const ray &r, const point<T1> &p)
    {
        if(r.is_degenerate())
            return p == r.p;
        auto v = (p - r.p);
        return parallel(v, r.v) and v * r.v > -EPS;
    }

    // Ray lies on ray check - O(1).
    template<typename T1>
    friend bool count(const ray &r, const ray<T1> &s)
    {
        if(!count(r, s.p))
            return false;
        else if(s.is_degenerate())
            return true;
        else if(r.is_degenerate())
            return false;
        return parallel(s.v, r.v) and s.v * r.v > -EPS;
    }

    // Ray lies on line check - O(1).
    template<typename T1>
    friend bool count(const line<T1> &l, const ray &r)
    {
        if(!count(l, r.p))
            return false;
        else if(r.is_degenerate())
            return true;
        else if(l.is_degenerate())
            return false;
        return parallel(r.v, l.v);
    }

    // Ray-ray coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const ray<T1> &s, const ray &r)
    {
        return coplanar(s.v, r.v, r.p - s.p);
    }

    // Ray-line coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const ray &r, const line<T1> &l)
    {
        return coplanar(r.v, l.v, l.p - r.p);
    }

    // Ray-ray parallelism check - O(1).
    template<typename T1>
    friend bool parallel(const ray<T1> &s, const ray &r)
    {
        return parallel(s.v, r.v);
    }

    // Ray-line parallelism check - O(1).
    template<typename T1>
    friend bool parallel(const ray &r, const line<T1> &l)
    {
        return parallel(r.v, l.v);
    }

    // Ray-ray concurrency check - O(1).
    template<typename T1>
    friend bool concurrent(const ray<T1> &s, const ray &r)
    {
        return coplanar(s, r) and !parallel(s, r);
    }

    // Ray-line concurrency check - O(1).
    template<typename T1>
    friend bool concurrent(const ray &r, const line<T1> &l)
    {
        return coplanar(r, l) and !parallel(r, l);
    }

    // Ray-ray orthogonality check - O(1).
    template<typename T1>
    friend bool orthogonal(const ray<T1> &s, const ray &r)
    {
        return perpendicular(s.v, r.v);
    }

    // Ray-line orthogonality check - O(1).
    template<typename T1>
    friend bool orthogonal(const ray &r, const line<T1> &l)
    {
        return perpendicular(r.v, l.v);
    }

    // Ray-ray perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const ray<T1> &s, const ray &r)
    {
        return coplanar(s, r) and orthogonal(s, r);
    }

    // Ray-line perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const ray &r, const line<T1> &l)
    {
        return coplanar(r, l) and orthogonal(r, l);
    }

    // Ray-ray intersection check - O(1).
    template<typename T1>
    friend bool intersect(const ray<T1> &s, const ray &r)
    {
        if(count(s, r.p) or count(r, s.p))
            return true;  // covers degenerate cases and collinear intersections (e.g.: s == r).
        line<T> l = {r.p, r.v};
        return intersect(s, l) and count(r, intersection(s, l).p);
    }

    // Ray-line intersection check - O(1).
    template<typename T1>
    friend bool intersect(const ray &r, const line<T1> &l)
    {
        line<T> s = {r.p, r.v};
        if(s == l)
            return true;
        else if(r.is_degenerate() and count(l, r.p))
            return true;
        else if(l.is_degenerate() and count(r, l.p))
            return true;
        return concurrent(s, l) and count(r, intersection(s, l).p);
    }

    // Ray-ray intersection - O(1).
    template<typename T1>
    friend auto intersection(const ray<T1> &s, const ray &r) -> tuple<bool, point<double>, point<double> >
    {
        assert(intersect(s, r));
        if(s == r or s.is_degenerate() or count(r, s))
            return {true, s.p, s.v};
        else if(r.is_degenerate() or count(s, r))
            return {true, r.p, r.v};
        else if(concurrent(s, r)) {
            auto res = intersection(s, line<T>(r.p, r.v));
            return {true, res.p, res.v};
        }
        return {false, s.p, r.p};
    }

    // Ray-line intersection - O(1).
    template<typename T1>
    friend ray<double> intersection(const ray &r, const line<T1> &l)
    {
        assert(intersect(r, l));
        line<T> s = {r.p, r.v};
        if(s == l or r.is_degenerate())
            return r;
        else if(l.is_degenerate())
            return {l.p, l.v};
        auto res = intersection(s, l);
        return {res.p, res.v};
    }

    // Point-ray distance - O(1).
    template<typename T1>
    friend double distance(const point<T1> &p, const ray &r)
    {
        if(r.is_degenerate() or (p - r.p) * r.v < EPS)
            return distance(p, r.p);
        return distance(p, line<T>(r.p, r.v));
    }

    // Ray-ray distance - O(1). // only 2d TODO 3d.
    template<typename T1>
    friend double distance(const ray<T1> &s, const ray &r)
    {
        if(r.is_degenerate())
            return distance(r.p, s);
        else if(s.is_degenerate())
            return distance(s.p, r);
        else if(parallel(s.v, r.v)) {
            if((r.p - s.p) * s.v > -EPS or (s.p - r.p) * r.v > -EPS) {
                if(collinear(s.p, r.p, r.p + r.v))
                    return 0;
                return distance(s.p, line<T>(r.p, r.v));
            }
            return distance(s.p, r.p);
        }
        else if(intersect(s, r))
            return 0;
        return min(distance(s.p, r), distance(r.p, s));
    }

    // Closest point in ray - O(1).
    template<typename T1>
    friend point<double> closest(const point<T1> &p, const ray &r)
    {
        if((p - r.p) * r.v < EPS)
            return r.p;
        return projection(p, line<T>(r.p, r.v));
    }

    // String conversion - O(1).
    friend string to_string(const ray &r)
    {
        return '[' + to_string(r.p) + ' ' + to_string(r.v) + ']';
    }

    // Output - O(1).
    friend ostream &operator<<(ostream &lhs, const ray &rhs)
    {
        return lhs << to_string(rhs);
    }
};
