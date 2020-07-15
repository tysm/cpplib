#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/utility/signum.hpp>

template<typename T,
typename enable_if<is_arithmetic<T>::value, uint>::type = 0>
struct point {
    T x, y, z;

    explicit point(const T x = 0, const T y = 0, const T z = 0) :
        x(x), y(y), z(z) {}

    template<typename T1>
    point(const point<T1> &p) :
        x(p.x), y(p.y), z(p.z) {}

    // Null vector check - O(1).
    bool is_null() const
    {
        return x == 0 and y == 0 and z == 0;
    }

    // Unit vector - O(1).
    point<double> as_unit() const
    {
        assert(!is_null());
        return (*this)/norm(*this);
    }

    // Negative vector - O(1).
    point operator-() const
    {
        return point(-x, -y, -z);
    }

    // Vector addiction assignment - O(1).
    template<typename T1>
    point &operator+=(const point<T1> &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    // Vector subtraction assignment - O(1).
    template<typename T1>
    point &operator-=(const point<T1> &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    // Vector cross product assignment - O(1).
    template<typename T1>
    point &operator^=(const point<T1> &rhs)
    {
        tie(x, y, z) = make_tuple(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
        return *this;
    }

    // Vector projection assignment - O(1).
    template<typename T1>
    point &operator>>=(const point<T1> &rhs)
    {
        if(rhs.is_null())
            tie(x, y, z) = make_tuple(0, 0, 0);
        else{
            auto res = ((*this)*rhs/squared_norm(rhs))*rhs;
            tie(x, y, z) = make_tuple(res.x, res.y, res.z);
        }
        return *this;
    }

    // Vector rejection assignment - O(1).
    template<typename T1>
    point &operator<<=(const point<T1> &rhs)
    {
        return *this -= (*this >> rhs);
    }

    // Scalar multiplication assignment - O(1).
    point &operator*=(const T rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    // Scalar division assignment - O(1).
    point &operator/=(const T rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    // Vector addiction - O(1).
    template<typename T1>
    friend auto operator+(const point &lhs, const point<T1> &rhs) -> point<typename common_type<T, T1>::type>
    {
        point<typename common_type<T, T1>::type> res(lhs);
        return res += rhs;
    }

    // Vector subtraction - O(1).
    template<typename T1>
    friend auto operator-(const point &lhs, const point<T1> &rhs) -> point<typename common_type<T, T1>::type>
    {
        point<typename common_type<T, T1>::type> res(lhs);
        return res -= rhs;
    }

    // Vector dot product - O(1).
    template<typename T1>
    friend auto operator*(const point &lhs, const point<T1> &rhs) -> typename common_type<T, T1>::type
    {
        return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
    }

    // Vector cross product - O(1).
    template<typename T1>
    friend auto operator^(const point &lhs, const point<T1> &rhs) -> point<typename common_type<T, T1>::type>
    {
        point<typename common_type<T, T1>::type> res(lhs);
        return res ^= rhs;
    }

    // Vector projection - O(1).
    template<typename T1>
    friend point<double> operator>>(const point &lhs, const point<T1> &rhs)
    {
        point<double> res(lhs);
        return res >>= rhs;
    }

    // Vector rejection - O(1).
    template<typename T1>
    friend point<double> operator<<(const point &lhs, const point<T1> &rhs)
    {
        point<double> res(lhs);
        return res <<= rhs;
    }

    // Scalar multiplication - O(1).
    template<typename T1,
    typename enable_if<is_arithmetic<T1>::value, uint>::type = 0>
    friend auto operator*(const point &lhs, const T1 rhs) -> point<typename common_type<T, T1>::type>
    {
        point<typename common_type<T, T1>::type> res(lhs);
        return res *= rhs;
    }

    // Scalar multiplication - O(1).
    template<typename T1,
    typename enable_if<is_arithmetic<T1>::value, uint>::type = 0>
    friend auto operator*(const T1 lhs, const point &rhs) -> point<typename common_type<T, T1>::type>
    {
        point<typename common_type<T1, T>::type> res(rhs);
        return res *= lhs;
    }

    // Scalar division - O(1).
    template<typename T1,
    typename enable_if<is_arithmetic<T1>::value, uint>::type = 0>
    friend auto operator/(const point &lhs, const T1 rhs) -> point<typename common_type<T, T1>::type>
    {
        point<typename common_type<T, T1>::type> res(lhs);
        return res /= rhs;
    }

    // Vector equal to - O(1).
    template<typename T1>
    friend bool operator==(const point &lhs, const point<T1> &rhs)
    {
        return tie(lhs.x, lhs.y, lhs.z) == tie(rhs.x, rhs.y, rhs.z);
    }

    // Vector not equal to - O(1).
    template<typename T1>
    friend bool operator!=(const point &lhs, const point<T1> &rhs)
    {
        return !(lhs == rhs);
    }

    // Vector less than - O(1).
    template<typename T1>
    friend bool operator<(const point &lhs, const point<T1> &rhs)
    {
        return tie(lhs.x, lhs.y, lhs.z) < tie(rhs.x, rhs.y, rhs.z);
    }

    // Vector greater than - O(1).
    template<typename T1>
    friend bool operator>(const point &lhs, const point<T1> &rhs)
    {
        return rhs < lhs;
    }

    // Vector less than or equal to - O(1).
    template<typename T1>
    friend bool operator<=(const point &lhs, const point<T1> &rhs)
    {
        return !(lhs > rhs);
    }

    // Vector greater than or equal to - O(1).
    template<typename T1>
    friend bool operator>=(const point &lhs, const point<T1> &rhs)
    {
        return !(lhs < rhs);
    }

    // Vector parallelism check - O(1).
    template<typename T1>
    friend bool parallel(const point &u, const point<T1> &v)
    {
        return (u^v).is_null();
    }

    // Vector coplanarity check - O(1).
    template<typename T1, typename T2>
    friend bool coplanar(const point &u, const point<T1> &v, const point<T2> &w)
    {
        return triple(u, v, w) == 0;
    }

    // Vector perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const point &u, const point<T1> &v)
    {
        return u*v == 0;
    }

    // Point collinearity check - O(1).
    template<typename T1, typename T2>
    friend bool collinear(const point &a, const point<T1> &b, const point<T2> &c)
    {
        return parallel(a - b, c - b);
    }

    // Vector triple product - O(1).
    template<typename T1, typename T2>
    friend auto triple(const point &u, const point<T1> &v, const point<T2> &w) -> typename common_type<T, T1, T2>::type
    {
        return (u^v)*w;
    }

    // Vector squared norm - O(1).
    friend T squared_norm(const point &v)
    {
        return v*v;
    }

    // Vector norm - O(1).
    friend double norm(const point &v)
    {
        return sqrt(squared_norm(v));
    }

    // Scalar projection - O(1).
    template<typename T1>
    friend double projection(const point &u, const point<T1> &v)
    {
        return v.is_null()? 0 : u*v/norm(v);
    }

    // Scalar rejection - O(1).
    template<typename T1>
    friend double rejection(const point &u, const point<T1> &v)
    {
        return norm(u << v);
    }

    // Point distance - O(1).
    template<typename T1>
    friend double distance(const point &a, const point<T1> &b)
    {
        return norm(b - a);
    }

    // Angle between two vectors - O(1).
    template<typename T1>
    friend double angle(const point &u, const point<T1> &v)
    {
        if(u.is_null() or v.is_null())
            return acos(0);
        auto aux = u*v/norm(u)/norm(v);
        return aux > 1? acos(1) : (aux < -1? acos(-1) : acos(aux));
    }

    // Angle between three points - O(1).
    template<typename T1, typename T2>
    friend double angle(const point &a, const point<T1> &b, const point<T2> &c)
    {
        return angle(a-b, c-b); // angle between b->a and b->c.
    }

    // Relative orientation of two vectors based on a third vector - O(1).
    template<typename T1, typename T2>
    friend int orientation(const point &u, const point<T1> &v, const point<T2> &w)
    {
        //  1 means counterclockwise.
        //  0 means (u, v, w) are coplanar.
        // -1 means clockwise.
        return sign(triple(u, v, w));
    }

    // Relative orientation of two vectors based on x, y, z axis - O(1).
    template<typename T1>
    friend tuple<int, int, int> orientation(const point &u, const point<T1> &v)
    {
        auto aux = u^v;
        //  1 means counterclockwise.
        //  0 means (u, v, axis) are coplanar.
        // -1 means clockwise.
        // (yTOz, zTOx, xTOy) == (x-axis, y-axis, z-axis).
        return make_tuple(sign(aux.x), sign(aux.y), sign(aux.z));
    }

    // Vector rotation - O(1).
    template<typename T1>
    friend point<double> rotate(const point &v, const point<T1> &u, double r)
    {
        assert(norm(u) == 1);
        double dot = v*u, co = cos(r), si = sin(r);
        double x = u.x*dot*(1 - co) + v.x*co + (u.y*v.z - u.z*v.y)*si;
        double y = u.y*dot*(1 - co) + v.y*co + (u.z*v.x - u.x*v.z)*si;
        double z = u.z*dot*(1 - co) + v.z*co + (u.x*v.y - u.y*v.x)*si;
        return point<double>(x, y, z);
    }

    // String conversion - O(1).
    friend string to_string(const point &p)
    {
        return '(' + to_string(p.x) + ' ' + to_string(p.y) + ' ' + to_string(p.z) + ')';
    }

    // Output - O(1).
    friend ostream &operator<<(ostream &lhs, const point &rhs)
    {
        return lhs << to_string(rhs);
    }
};
