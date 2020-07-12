#pragma once
#include <cpplib/stdinc.hpp>
#include <cpplib/utility/signum.hpp>

template<typename T,
typename enable_if<is_arithmetic<T>::value, uint>::type = 0>
struct Point {
    T x, y, z;

    explicit Point(const T x = 0, const T y = 0, const T z = 0) :
        x(x), y(y), z(z) {}

    template<typename T1>
    Point(const Point<T1> &p) :
        x(p.x), y(p.y), z(p.z) {}

    // Component sum - O(1).
    T operator+() const
    {
        return x + y + z;
    }

    // Negative vector - O(1).
    Point operator-() const
    {
        return Point(-x, -y, -z);
    }

    // Unit vector - O(1).
    Point<double> operator~() const
    {
        return (*this)/norm(*this);
    }

    // Vector squared norm - O(1).
    T operator!() const
    {
        return (*this)*(*this);
    }

    // Vector addiction assignment - O(1).
    template<typename T1>
    Point &operator+=(const Point<T1> &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    // Vector subtraction assignment - O(1).
    template<typename T1>
    Point &operator-=(const Point<T1> &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    // Vector cross product assignment - O(1).
    template<typename T1>
    Point &operator^=(const Point<T1> &rhs)
    {
        tie(x, y, z) = make_tuple(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
        return *this;
    }

    // Vector projection assignment - O(1).
    template<typename T1>
    Point &operator>>=(const Point<T1> &rhs)
    {
        auto res = ((*this)*rhs/(!rhs))*rhs;
        tie(x, y, z) = make_tuple(res.x, res.y, res.z);
        return *this;
    }

    // Vector rejection assignment - O(1).
    template<typename T1>
    Point &operator<<=(const Point<T1> &rhs)
    {
        return *this -= (*this >> rhs);
    }

    // Scalar multiplication assignment - O(1).
    Point &operator*=(const T rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    // Scalar division assignment - O(1).
    Point &operator/=(const T rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    // Vector addiction - O(1).
    template<typename T1>
    friend auto operator+(const Point &lhs, const Point<T1> &rhs) -> Point<typename common_type<T, T1>::type>
    {
        Point<typename common_type<T, T1>::type> res(lhs);
        return res += rhs;
    }

    // Vector subtraction - O(1).
    template<typename T1>
    friend auto operator-(const Point &lhs, const Point<T1> &rhs) -> Point<typename common_type<T, T1>::type>
    {
        Point<typename common_type<T, T1>::type> res(lhs);
        return res -= rhs;
    }

    // Vector dot product - O(1).
    template<typename T1>
    friend auto operator*(const Point &lhs, const Point<T1> &rhs) -> typename common_type<T, T1>::type
    {
        return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
    }

    // Vector cross product - O(1).
    template<typename T1>
    friend auto operator^(const Point &lhs, const Point<T1> &rhs) -> Point<typename common_type<T, T1>::type>
    {
        Point<typename common_type<T, T1>::type> res(lhs);
        return res ^= rhs;
    }

    // Vector projection - O(1).
    template<typename T1>
    friend Point<double> operator>>(const Point &lhs, const Point<T1> &rhs)
    {
        Point<double> res(lhs);
        return res >>= rhs;
    }

    // Vector rejection - O(1).
    template<typename T1>
    friend Point<double> operator<<(const Point &lhs, const Point<T1> &rhs)
    {
        Point<double> res(lhs);
        return res <<= rhs;
    }

    // Scalar multiplication - O(1).
    template<typename T1,
    typename enable_if<is_arithmetic<T1>::value, uint>::type = 0>
    friend auto operator*(const Point &lhs, const T1 rhs) -> Point<typename common_type<T, T1>::type>
    {
        Point<typename common_type<T, T1>::type> res(lhs);
        return res *= rhs;
    }

    // Scalar multiplication - O(1).
    template<typename T1,
    typename enable_if<is_arithmetic<T1>::value, uint>::type = 0>
    friend auto operator*(const T1 lhs, const Point &rhs) -> Point<typename common_type<T, T1>::type>
    {
        Point<typename common_type<T1, T>::type> res(rhs);
        return res *= lhs;
    }

    // Scalar division - O(1).
    template<typename T1,
    typename enable_if<is_arithmetic<T1>::value, uint>::type = 0>
    friend auto operator/(const Point &lhs, const T1 rhs) -> Point<typename common_type<T, T1>::type>
    {
        Point<typename common_type<T, T1>::type> res(lhs);
        return res /= rhs;
    }

    // Vector equal to - O(1).
    template<typename T1>
    friend bool operator==(const Point &lhs, const Point<T1> &rhs)
    {
        return tie(lhs.x, lhs.y, lhs.z) == tie(rhs.x, rhs.y, rhs.z);
    }

    // Vector not equal to - O(1).
    template<typename T1>
    friend bool operator!=(const Point &lhs, const Point<T1> &rhs)
    {
        return !(lhs == rhs);
    }

    // Vector less than - O(1).
    template<typename T1>
    friend bool operator<(const Point &lhs, const Point<T1> &rhs)
    {
        return tie(lhs.x, lhs.y, lhs.z) < tie(rhs.x, rhs.y, rhs.z);
    }

    // Vector greater than - O(1).
    template<typename T1>
    friend bool operator>(const Point &lhs, const Point<T1> &rhs)
    {
        return rhs < lhs;
    }

    // Vector less than or equal to - O(1).
    template<typename T1>
    friend bool operator<=(const Point &lhs, const Point<T1> &rhs)
    {
        return !(lhs > rhs);
    }

    // Vector greater than or equal to - O(1).
    template<typename T1>
    friend bool operator>=(const Point &lhs, const Point<T1> &rhs)
    {
        return !(lhs < rhs);
    }

    // Vector triple product - O(1).
    template<typename T1, typename T2>
    friend auto triple(const Point &a, const Point<T1> &b, const Point<T2> &c) -> typename common_type<T, T1, T2>::type
    {
        return a*(b^c);
    }

    // Vector norm - O(1).
    friend double norm(const Point &p)
    {
        return sqrt(!p);
    }

    // Scalar projection - O(1).
    template<typename T1>
    friend double projection(const Point &a, const Point<T1> &b)
    {
        return a*b/norm(b);
    }

    // Scalar rejection - O(1).
    template<typename T1>
    friend double rejection(const Point &a, const Point<T1> &b)
    {
        return norm(a - (a >> b));
    }

    // Point distance - O(1).
    template<typename T1>
    friend double distance(const Point &a, const Point<T1> &b)
    {
        return norm(a - b);
    }

    // Angle between two vectors - O(1).
    template<typename T1>
    friend double angle(const Point &a, const Point<T1> &b)
    {
        auto aux = a*b/norm(a)/norm(b);
        return aux > 1? acos(1) : (aux < -1? acos(-1) : acos(aux));
    }

    // Angle between three points - O(1).
    template<typename T1, typename T2>
    friend double angle(const Point &a, const Point<T1> &b, const Point<T2> &c)
    {
        return angle(a-b, c-b); // angle between b->a and b->c.
    }

    // Angle counterclockwise orientation between two vectors - O(1).
    template<typename T1>
    friend tuple<int, int, int> orientation(const Point &a, const Point<T1> &b)
    {
        auto aux = a^b;
        //  1 means counterclockwise.
        //  0 means the target component is collinear.
        // -1 means clockwise.
        // (yTOz, zTOx, xTOy) == (x-axis, y-axis, z-axis).
        return make_tuple(sign(aux.x), sign(aux.y), sign(aux.z));
    }

    // Vector string conversion - O(1).
    friend string to_string(const Point &p)
    {
        return '(' + to_string(p.x) + ' ' + to_string(p.y) + ' ' + to_string(p.z) + ')';
    }

    // Vector output - O(1).
    friend ostream &operator<<(ostream &lhs, const Point &rhs)
    {
        return lhs << to_string(rhs);
    }
};
