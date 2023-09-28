#ifndef FLEURS_POINT_HPP
#define FLEURS_POINT_HPP 1

#include <cmath>
#include <iostream>

namespace fleurs {

template <typename T>
struct Point {
    T x{}, y{};

    Point() = default;
    Point(T x, T y) : x(x), y(y) {}

    Point operator-() const { return Point(-x, -y); }
    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator*(T s) const { return Point(x * s, y * s); }

    bool operator==(const Point &p) const { return x == p.x && y == p.y; }
    bool operator!=(const Point &p) const { return !(p == *this); }
    bool operator<(const Point &p) const { return x < p.x || (x == p.x && y < p.y); }

    T dot(const Point &p) const { return x * p.x + y * p.y; }
    T cross(const Point &p) const { return x * p.y - y * p.x; }
    T abs() const { return std::hypot(x, y); }
    T angle() const { return std::atan2(y, x); }
    T distance(const Point &p) const { return (p - *this).abs(); }

    Point rotate(double theta) const {
        return Point(std::cos(theta) * x - std::sin(theta) * y, std::sin(theta) * x + std::cos(theta) * y);
    }
    Point rotate90() const { return Point(-y, x); }
    Point normalize() const { return *this * (1.0 / abs()); }

    friend std::ostream &operator<<(std::ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
    friend std::istream &operator>>(std::istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
};

} // namespace fleurs

#endif // FLEURS_POINT_HPP

