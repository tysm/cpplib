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

    // Not null vector check - O(1).
    explicit operator bool() const
    {
        return x or y or z;
    }

    // Negative vector - O(1).
    point operator-() const
    {
        return point(-x, -y, -z);
    }

    // Unit vector - O(1).
    point<double> operator~() const
    {
        assert(*this);
        return (*this)/norm(*this);
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
        if(!rhs)
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
    friend bool parallel(const point &a, const point<T1> &b)
    {
        return !(a^b);
    }

    // Vector coplanarity check - O(1).
    template<typename T1, typename T2>
    friend bool coplanar(const point &u, const point<T1> &v, const point<T2> &w)
    {
        return triple(u, v, w) == 0;
    }

    // Vector perpendicularity check - O(1).
    template<typename T1>
    friend bool perpendicular(const point &a, const point<T1> &b)
    {
        return a*b == 0;
    }

    // Point collinearity check - O(1).
    template<typename T1, typename T2>
    friend bool collinear(const point &a, const point<T1> &b, const point<T2> &c)
    {
        return parallel(a - b, c - b);
    }

    // Vector triple product - O(1).
    template<typename T1, typename T2>
    friend auto triple(const point &a, const point<T1> &b, const point<T2> &c) -> typename common_type<T, T1, T2>::type
    {
        return a*(b^c);
    }

    // Vector squared norm - O(1).
    friend T squared_norm(const point &p)
    {
        return p*p;
    }

    // Vector norm - O(1).
    friend double norm(const point &p)
    {
        return sqrt(squared_norm(p));
    }

    // Scalar projection - O(1).
    template<typename T1>
    friend double projection(const point &a, const point<T1> &b)
    {
        return !b? 0 : a*b/norm(b);
    }

    // Scalar rejection - O(1).
    template<typename T1>
    friend double rejection(const point &a, const point<T1> &b)
    {
        return norm(a << b);
    }

    // Point distance - O(1).
    template<typename T1>
    friend double distance(const point &a, const point<T1> &b)
    {
        return norm(b - a);
    }

    // Angle between two vectors - O(1).
    template<typename T1>
    friend double angle(const point &a, const point<T1> &b)
    {
        if(!a or !b)
            return acos(0);
        auto aux = a*b/norm(a)/norm(b);
        return aux > 1? acos(1) : (aux < -1? acos(-1) : acos(aux));
    }

    // Angle between three points - O(1).
    template<typename T1, typename T2>
    friend double angle(const point &a, const point<T1> &b, const point<T2> &c)
    {
        return angle(a-b, c-b); // angle between b->a and b->c.
    }

    // Angle counterclockwise orientation between two vectors - O(1).
    template<typename T1>
    friend tuple<int, int, int> orientation(const point &a, const point<T1> &b)
    {
        auto aux = a^b;
        //  1 means counterclockwise.
        //  0 means the target component is collinear.
        // -1 means clockwise.
        // (yTOz, zTOx, xTOy) == (x-axis, y-axis, z-axis).
        return make_tuple(sign(aux.x), sign(aux.y), sign(aux.z));
    }

    // Vector rotation - O(1).
    template<typename T1>
    friend point<double> rotate(const point &p, const point<T1> &u, double a)
    {
        assert(norm(u) == 1);
        double dot = p*u, co = cos(a), si = sin(a);
        double x = u.x*dot*(1 - co) + p.x*co + (u.y*p.z - u.z*p.y)*si;
        double y = u.y*dot*(1 - co) + p.y*co + (u.z*p.x - u.x*p.z)*si;
        double z = u.z*dot*(1 - co) + p.z*co + (u.x*p.y - u.y*p.x)*si;
        return point<double>(x, y, z);
    }

    // Vector string conversion - O(1).
    friend string to_string(const point &p)
    {
        return '(' + to_string(p.x) + ' ' + to_string(p.y) + ' ' + to_string(p.z) + ')';
    }

    // Vector output - O(1).
    friend ostream &operator<<(ostream &lhs, const point &rhs)
    {
        return lhs << to_string(rhs);
    }
};
