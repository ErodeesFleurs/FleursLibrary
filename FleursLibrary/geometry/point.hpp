#ifndef FLEURS_POINT_HPP
#define FLEURS_POINT_HPP 1

#include<bits/stdc++.h>
#include<FleursLibrary/geometry/base>

namespace fleurs {

template <typename T>
struct Point {
    T x, y;

    Point() = default;

    Point(T x, T y) : x(x), y(y) {}
    Point(const Point<T>& p) : x(p.x), y(p.y) {}
    Point(std::pair<T, T> p) : x(p.first), y(p.second) {}

    Point operator-(void) const {
        return Point<T>(-x, -y);
    }
    Point<T>& operator=(const Point<T>& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
    Point<T>& operator=(std::pair<T, T> p) {
        x = p.first;
        y = p.second;
        return *this;
    }
    Point<T> operator+(const Point<T>& p) const {
        return Point<T>(x + p.x, y + p.y);
    }
    Point<T>& operator+=(const Point<T>& p) {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point<T> operator-(const Point<T>& p) const {
        return Point<T>(x - p.x, y - p.y);
    }
    Point<T>& operator-=(const Point<T>& p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point operator*(T s) const {
        return Point<T>(x * s, y * s);
    }
    bool operator==(const Point<T>& p) const {
        return x == p.x && y == p.y;
    }
    bool operator!=(const Point<T>& p) const {
        return x != p.x || y != p.y;
    }
    bool operator<(const Point<T>& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator>(const Point<T>& p) const {
        return x > p.x || (x == p.x && y > p.y);
    }
    T dot(const Point<T>& p) const {
        return x * p.x + y * p.y;
    }
    T cross(const Point<T>& p) const {
        return x * p.y - y * p.x;
    }
    T norm() const {
        return x * x + y * y;
    }
    T abs() const {
        return std::sqrt(norm());
    }
    T angle() const {
        return std::atan2(y, x);
    }
    T angle(const Point<T>& p) const {
        return std::atan2(cross(p), dot(p));
    }
    T angle(const Point<T>& a, const Point<T>& b) const {
        return (a - *this).angle(b - *this);
    }
    T distance(const Point<T>& p) const {
        return (p - *this).abs();
    }
    T distance(const Point<T>& a, const Point<T>& b) const {
        return std::abs((a - *this).cross(b - *this)) / (a - b).abs();
    }

    // rotate this point counterclockwise by theta rad
    Point<T> rotate(double theta) const {
        return Point<T>(std::cos(theta) * x - std::sin(theta) * y,
                        std::sin(theta) * x + std::cos(theta) * y);
    }
    // rotate point p around this point counterclockwise by theta rad
    Point<T> rotate(double theta, const Point<T>& p) const {
        return (p - *this).rotate(theta) + *this;
    }
    Point<T> rotate90() const {
        return Point<T>(-y, x);
    }
    Point<T> normalize() const {
        return *this * (1.0 / abs());
    }
    Point<T> normalize(const Point<T>& p) const {
        return (*this - p).normalize() + p;
    }
    Point<T> normal() const {
        return rotate90().normalize();
    }

    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Point<T>& p) {
        is >> p.x >> p.y;
        return is;
    }
};

}  // namespace fleurs

#endif  // FLEURS_POINT_HPP