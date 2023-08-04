#ifndef FLEURS_POINT_TRD_HPP
#define FLEURS_POINT_TRD_HPP 1

#include <FleursLibrary/geometry/base.hpp>
#include <cmath>

namespace fleurs{
template<typename T>
struct Point3d {
    T x, y, z;
    Point3d() : x(0), y(0), z(0) {}
    Point3d(T x, T y, T z) : x(x), y(y), z(z) {}
    
    Point3d operator+(const Point3d& p) const { return Point3d(x + p.x, y + p.y, z + p.z); }
    Point3d operator-(const Point3d& p) const { return Point3d(x - p.x, y - p.y, z - p.z); }
    Point3d operator*(const T& k) const { return Point3d(x * k, y * k, z * k); }
    Point3d operator/(const T& k) const { return Point3d(x / k, y / k, z / k); }
    Point3d& operator+=(const Point3d& p) { x += p.x, y += p.y, z += p.z; return *this; }
    Point3d& operator-=(const Point3d& p) { x -= p.x, y -= p.y, z -= p.z; return *this; }
    Point3d& operator*=(const T& k) { x *= k, y *= k, z *= k; return *this; }
    Point3d& operator/=(const T& k) { x /= k, y /= k, z /= k; return *this; }
    
    bool operator==(const Point3d& p) const { return equals(x, p.x) && equals(y, p.y) && equals(z, p.z); }
    bool operator!=(const Point3d& p) const { return !equals(x, p.x) || !equals(y, p.y) || !equals(z, p.z); }
    bool operator<(const Point3d& p) const { return !equals(x, p.x) ? x < p.x : !equals(y, p.y) ? y < p.y : z < p.z; }
    bool operator>(const Point3d& p) const { return !equals(x, p.x) ? x > p.x : !equals(y, p.y) ? y > p.y : z > p.z; }
    bool operator<=(const Point3d& p) const { return !equals(x, p.x) ? x < p.x : !equals(y, p.y) ? y < p.y : z <= p.z; }
    bool operator>=(const Point3d& p) const { return !equals(x, p.x) ? x > p.x : !equals(y, p.y) ? y > p.y : z >= p.z; }

    T dot(const Point3d& p) const { return x * p.x + y * p.y + z * p.z; }
    Point3d cross(const Point3d& p) const { return Point3d(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
    T norm() const { return x * x + y * y + z * z; }
    T abs() const { return std::sqrt(norm()); }
    T distance(const Point3d& p) const { return (*this - p).abs(); }
    Point3d normalize() const { return *this / abs(); }
    T angle(const Point3d& p) const { return std::acos(dot(p) / (abs() * p.abs())); }
    T angle(const Point3d& p1, const Point3d& p2) const { return (p1 - *this).angle(p2 - *this); }
    T length() const { return abs(); }

    Point3d rotateX(T rad) const { return Point3d(x, y * std::cos(rad) - z * std::sin(rad), y * std::sin(rad) + z * std::cos(rad)); }
    Point3d rotateY(T rad) const { return Point3d(x * std::cos(rad) + z * std::sin(rad), y, -x * std::sin(rad) + z * std::cos(rad)); }
    Point3d rotateZ(T rad) const { return Point3d(x * std::cos(rad) - y * std::sin(rad), x * std::sin(rad) + y * std::cos(rad), z); }
    Point3d rotate(const Point3d& axis, T rad) const { return (*this - axis).rotateZ(rad) + axis; }
    Point3d rotate(const Point3d& axis, const Point3d& dir, T rad) const { return (*this - axis).rotate(dir, rad) + axis; }

    friend std::ostream& operator<<(std::ostream& os, const Point3d& p) { return os << '(' << p.x << ", " << p.y << ", " << p.z << ')'; }
    friend std::istream& operator>>(std::istream& is, Point3d& p) { return is >> p.x >> p.y >> p.z; }
};

} // namespace fleurs



#endif // FLEURS_POINT_TRD_HPP