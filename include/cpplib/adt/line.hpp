#pragma once
#include <cpplib/adt/point.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
struct line
{
    point<T> p, v;

    line() {}

    template<typename T1, typename T2>
    line(const point<T1> &p, const point<T2> &v) :
        p(p), v(v)
    {}

    template<typename T1>
    line(const line<T1> &l) :
        p(l.p), v(l.v)
    {}

    // Degenerate line check - O(1).
    bool is_degenerate() const
    {
        return v.is_null();
    }

    // Point on line - O(1).
    template<typename T1,
        typename enable_if<is_arithmetic<T1>::value, uint>::type = 0>
    auto at(const T1 k) const -> point<typename common_type<T, T1>::type>
    {
        return p + k * v;
    }

    // Line equivalent to - O(1).
    template<typename T1>
    friend bool operator==(const line &lhs, const line<T1> &rhs)
    {
        if(lhs.is_degenerate() and rhs.is_degenerate())
            return lhs.p == rhs.p;
        else if(!lhs.is_degenerate() and !rhs.is_degenerate())
            return parallel(lhs, rhs) and count(lhs, rhs.p);
        return false;
    }

    // Line not equivalent to - O(1).
    template<typename T1>
    friend bool operator!=(const line &lhs, const line<T1> &rhs)
    {
        return !(lhs == rhs);
    }

    // Point lies on line check - O(1).
    template<typename T1>
    friend bool count(const line &l, const point<T1> &p)
    {
        return l.is_degenerate() ? p == l.p : parallel((p - l.p), l.v);
    }

    // Line coplanarity check - O(1).
    template<typename T1>
    friend bool coplanar(const line<T1> &r, const line &l)
    {
        return coplanar(r.v, l.v, l.p - r.p);
    }

    // Line parallelism check - O(1).
    template<typename T1>
    friend bool parallel(const line<T1> &r, const line &l)
    {
        return parallel(r.v, l.v);
    }

    // Line concurrency check - O(1).
    template<typename T1>
    friend bool concurrent(const line<T1> &r, const line &l)
    {
        return coplanar(r, l) and !parallel(r, l);
    }

    // Line orthogonality check - O(1).
    template<typename T1>
    friend bool orthogonal(const line<T1> &r, const line &l)
    {
        return perpendicular(r.v, l.v);
    }

    // Line perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const line<T1> &r, const line &l)
    {
        return coplanar(r, l) and orthogonal(r, l);
    }

    // Line intersection check - O(1).
    template<typename T1>
    friend bool intersect(const line<T1> &r, const line &l)
    {
        if(r == l)
            return true;
        else if(r.is_degenerate() and count(l, r.p))
            return true;
        else if(l.is_degenerate() and count(r, l.p))
            return true;
        return concurrent(r, l);
    }

    // Line intersection - O(1).
    template<typename T1>
    friend line<double> intersection(const line<T1> &r, const line &l)
    {
        assert(intersect(r, l));
        if(r == l or r.is_degenerate())
            return r;
        else if(l.is_degenerate())
            return l;
        auto rl = l.p - r.p;
        double k = sqrt((double)squared_norm(rl ^ l.v) / squared_norm(r.v ^ l.v));
        return {r.at(k * orientation(rl, l.v, r.v ^ l.v)), point<double>()};
    }

    // Point distance - O(1).
    template<typename T1>
    friend double distance(const point<T1> &p, const line &l)
    {
        if(l.is_degenerate())
            return distance(p, l.p);
        return sqrt((double)squared_norm((p - l.p) ^ l.v) / squared_norm(l.v));
    }

    // Line distance - O(1).
    template<typename T1>
    friend double distance(const line<T1> &r, const line &l)
    {
        if(l.is_degenerate())
            return distance(l.p, r);
        else if(r.is_degenerate() or parallel(r, l))
            return distance(r.p, l);
        return abs((l.p - r.p) * (r.v ^ l.v)) / norm(r.v ^ l.v);
    }

    // Point projection onto line - O(1).
    template<typename T1>
    friend point<double> projection(const point<T1> &p, const line &l)
    {
        point<double> res = l.p;
        if(!l.is_degenerate())
            res += l.v * ((double)((p - l.p) * l.v) / squared_norm(l.v));
        return res;
    }

    // Line projection onto line - O(1).
    template<typename T1>
    friend line<double> projection(const line<T1> &r, const line &l)
    {
        auto p = projection(r.p, l), q = projection(r.p + r.v, l);
        return {p, q - p};
    }

    // Point reflection over line - O(1).
    template<typename T1>
    friend point<double> reflection(const point<T1> &p, const line &l)
    {
        return 2 * projection(p, l) - p;
    }

    // Line reflection over line - O(1).
    template<typename T1>
    friend line<double> reflection(const line<T1> &r, const line &l)
    {
        auto p = reflection(r.p, l), q = reflection(r.p + r.v, l);
        return {p, q - p};
    }

    // String conversion - O(1).
    friend string to_string(const line &l)
    {
        return '[' + to_string(l.p) + ' ' + to_string(l.v) + ']';
    }

    // Output - O(1).
    friend ostream &operator<<(ostream &lhs, const line &rhs)
    {
        return lhs << to_string(rhs);
    }
};

line<double> make_line2d(const double a, const double b, const double c)
{
    point<double> p, v(-b, a);
    if(abs(a) >= EPS)
        p = {-c / a, 0};
    else
        p = {0, -c / b};
    return line<double>(p, v);
}

template<typename T>
tuple<T, T, T> line2d_coefficients(const line<T> &l)
{
    assert(abs(l.p.z) < EPS and abs(l.v.z) < EPS);
    auto p = l.p, q = l.p + l.v;
    return {q.y - p.y, p.x - q.x, p.y * q.x - p.x * q.y};
}
