#pragma once
#include <cpplib/adt/line.hpp>
#include <cpplib/adt/point.hpp>
#include <cpplib/stdinc.hpp>

template<typename T>
struct circle
{
    T r;
    point<T> c;

    template<typename T1, typename T2>
    circle(const point<T1> &c, const T2 r) :
        c(c), r(r)
    {}

    // Degenerate circle check - O(1).
    bool is_degenerate() const
    {
        return abs(r) < EPS;
    }

    // Area - O(1).
    double area() const
    {
        return PI * r * r;
    }

    // Diameter - O(1).
    T diameter() const
    {
        return 2 * r;
    }

    // Circumference - O(1).
    double circumference() const
    {
        return 2 * PI * r;
    }

    // Arc length - O(1).
    double arc(const double ang) const
    {
        return ang * r;  // (ang/(2*PI))*(2*PI*r).
    }

    // Sector area - O(1).
    double sector(const double ang) const
    {
        return (ang / 2) * r * r;  // (ang/(2*PI))*(PI*r*r).
    }

    // Chord length - O(1).
    double chord(const double ang) const
    {
        return 2 * r * sinl(ang / 2);  // same as sqrt(2*r*r*(1-acosl(ang))) by the Law of Cosines.
    }

    // Segment area - O(1).
    double segment(const double ang) const
    {
        double b = circle_chord(r, ang);
        double h = r * cosl(ang / 2);
        double chord_area = b * h / 2;
        return circle_sector(r, ang) - chord_area;
    }

    // Tangents from external point - O(1).
    template<typename T1>
    tuple<point<double>, point<double> > tangents(const point<T1> &p) const
    {
        // see tangents-from-external-point.png.
        double h = distance(p, c), x = sqrt(h * h - r * r), ang = asinl(r / h);
        auto v = c - p;
        // the points are given in ccw order with the circle center as referential.
        // this means that if you pick the vector from the center to the first point
        // and rotate it in ccw you will reach the second point.
        return {p + rotate(v, OZ, ang) * x / h, p + rotate(v, OZ, -ang) * x / h};
    }

    // Circle equivalent to - O(1).
    template<typename T1>
    friend bool operator==(const circle &lhs, const circle<T1> &rhs)
    {
        return lhs.c == rhs.c and abs(lhs.r - rhs.r) < EPS;
    }

    // Circle not equivalent to - O(1).
    template<typename T1>
    friend bool operator!=(const circle &lhs, const circle<T1> &rhs)
    {
        return !(lhs == rhs);
    }

    // Point inside check (p inside a?) - O(1).
    template<typename T1>
    friend int count(const circle &a, const point<T1> &p)
    {
        auto d = p - a.c;               // (dx, dy).
        auto res = d * d;               // dx*dx + dy*dy.
        if(abs(a.r * a.r - res) < EPS)  // dx*dx + dy*dy == r*r -> border.
            return 2;
        if(res <= a.r * a.r - EPS)  // dx*dx + dy*dy < r*r -> inside.
            return 1;
        return 0;  // dx*dx + dy*dy > r*r -> outside.
    }

    // Circle inside check (b inside a?) - O(1).
    template<typename T1>
    friend int count(const circle &a, const circle<T1> &b)
    {
        if(b == a)  // same.
            return 2;

        if(b.r >= a.r + EPS)  // greater, thus not inside.
            return 0;

        auto squared_rdiff = a.r - b.r;  // squared radii difference.
        squared_rdiff *= squared_rdiff;
        if(squared_norm(a.c - b.c) < squared_rdiff + EPS)  // inside.
            return 1;
        return 0;  // not inside.
    }

    // Line intersection check - O(1).
    template<typename T1>
    friend int intersect(const line<T1> &l, const circle &a)
    {
        auto d = distance(a.c, l);
        if(abs(d - a.r) < EPS)  // border -> intersect in one point.
            return 2;
        else if(d <= a.r - EPS)  // intersect in two points.
            return 1;
        return 0;  // don't intersect.
    }

    // Circle intersection check - O(1).
    template<typename T1>
    friend int intersect(const circle<T1> &b, const circle &a)
    {
        if(b == a)  // same -> intersect in many points.
            return 3;

        auto sqd = squared_norm(a.c - b.c);  // squared distance between their centers.

        auto squared_rdiff = a.r - b.r;  // squared radii difference.
        squared_rdiff *= squared_rdiff;

        if(abs(sqd - squared_rdiff) < EPS)  // one is inside another and they intersect in one point.
            return 2;

        auto squared_rsum = a.r + b.r;  // squared raii sum.
        squared_rsum *= squared_rsum;

        if(abs(sqd - squared_rsum) < EPS)  // border -> intersect in one point.
            return 2;

        if(sqd >= squared_rsum + EPS or count(b, a) or count(a, b))  // don't intersect.
            return 0;

        return 1;  // intersect in two points.
    }

    // Line intersection - O(1).
    template<typename T1>
    friend tuple<point<double>, point<double> > intersection(const line<T1> &l, const circle &a)
    {
        int check = intersect(l, a);
        assert(check);

        auto res = projection(a.c, l);  // closest point in line.
        if(check == 2)                  // intersection in one point.
            return {res, res};

        if(res == a.c) {  // line crosses the center of the circle.
            auto dir = l.v * a.r / norm(l.v);
            return {res - dir, res + dir};
        }

        auto v = res - a.c;                           // vector to the closest point in line.
        double sqd = squared_norm(v), d = sqrt(sqd);  // distance to the closest point in line.

        double w = sqrt(a.r * a.r - sqd);  // distance between that point and the intersection points.

        swap(v.x, v.y);  // ccw rotate that vector in 90 degrees.
        v.x = -v.x;

        auto dir = v * w / d;
        // the points are given in order of the line vector.
        if(dir * l.v >= EPS)
            return {res - dir, res + dir};
        return {res + dir, res - dir};
    }

    // Circle intersection - O(1).
    template<typename T1>
    friend tuple<point<double>, point<double> > intersection(const circle<T1> &b, const circle &a)
    {
        int check = intersect(b, a);
        assert(check);
        if(check == 3)  // they are the same, returning two points.
            return {b.c + OX * b.r, b.c - OX * b.r};

        auto ac = a.c - b.c;
        auto l = make_line2d(-2 * ac.x, -2 * ac.y, ac.x * ac.x + ac.y * ac.y + b.r * b.r - a.r * a.r);
        circle<T1> c(point<T1>(0, 0), b.r);

        auto res = intersection(l, c);
        // the points are given in ccw order with the center of the first circle as referential.
        // this means that if you pick the vector from the center to the first point
        // and rotate it in ccw you will reach the second point.
        return {get<1>(res) + b.c, get<0>(res) + b.c};
    }

    // Circle intersection area - O(1).
    template<typename T1>
    friend double intersection_area(const circle<T1> &b, const circle &a)
    {
        if(count(b, a))  // a in b.
            return a.area();
        else if(count(a, b))  // b in a.
            return b.area();

        // see circle-circle-intersection-area.jpg.
        if(intersect(b, a) != 1)
            return 0;

        double d = distance(a.c, b.c);
        double sqd = d * d;

        double sqar = a.r * a.r;
        double sqbr = b.r * b.r;

        // law of cosines.
        double alpha = acosl((sqd + (a.r - b.r) * (a.r + b.r)) / (2 * d * a.r));
        double res_a = sqar * (alpha - 0.5 * sinl(2 * alpha));

        double beta = acosl((sqd + (b.r - a.r) * (b.r + a.r)) / (2 * d * b.r));
        double res_b = sqbr * (beta - 0.5 * sinl(2 * beta));

        return res_a + res_b;
    }

    // String conversion - O(1).
    friend string to_string(const circle &a)
    {
        return '[' + to_string(a.c) + ' ' + to_string(a.r) + ']';
    }

    // Output - O(1).
    friend ostream &operator<<(ostream &lhs, const circle &rhs)
    {
        return lhs << to_string(rhs);
    }
};
