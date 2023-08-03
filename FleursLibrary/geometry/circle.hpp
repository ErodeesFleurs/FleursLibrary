#ifndef FLEURS_CIRCLE_HPP
#define FLEURS_CIRCLE_HPP 1

#include<FleursLibrary/geometry/segment>

namespace fleurs {

template <typename T>
struct Circle {
    Point<T> center;
    T radius;
    Circle() = default;
    Circle(Point<T> center, T radius) : center(center), radius(radius) {}
    Circle(T x, T y, T radius) : center(x, y), radius(radius) {}
    Circle(const Circle<T>& c) : center(c.center), radius(c.radius) {}
    Circle(const Point<T>& p1, const Point<T>& p2) {
        center = Point<T>((p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0);
        radius = (p1 - center).abs();
    }
    Circle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        Point<T> a = p2 - p1;
        Point<T> b = p3 - p1;
        T c = a.abs();
        T d = b.abs();
        T e = a.dot(b) / c;
        T f = a.cross(b) / c;
        center = Point<T>(p1.x + (d * e * f) / (c * c), p1.y + (d * f * f) / (c * c));
        radius = (p1 - center).abs();
    }
    bool operator==(const Circle<T>& c) const {
        return center == c.center && radius == c.radius;
    }
    bool operator!=(const Circle<T>& c) const {
        return center != c.center || radius != c.radius;
    }
    Circle<T>& operator=(const Circle<T>& c) {
        center = c.center;
        radius = c.radius;
        return *this;
    }
    bool contains(const Point<T>& p) const {
        return equals((p - center).abs(), radius);
    }
    bool contains(const Circle<T>& c) const {
        return equals((c.center - center).abs() + c.radius, radius);
    }
    bool intersects(const Circle<T>& c) const {
        return !contains(c) && !c.contains(*this) && (center - c.center).abs() <= radius + c.radius;
    }
    bool intersects(const Point<T>& p) const {
        return equals((p - center).abs(), radius);
    }
    bool intersects(const Segment<T>& s) const {
        return (s.a - center).abs() <= radius || (s.b - center).abs() <= radius || (center - s.a).abs() <= radius && (center - s.b).abs() <= radius && s.distance(center) <= radius;
    }
    bool intersects(const Line<T>& l) const {
        return l.distance(center) <= radius;
    }
    std::pair<Point<T>, Point<T>> getCrossPoints(const Circle<T>& c) const {
        Point<T> a = c.center - center;
        T d = a.abs();
        T e = (square(radius) - square(c.radius) + square(d)) / (2.0 * d);
        T f = sqrt(square(radius) - square(e));
        Point<T> p = center + a * (e / d);
        Point<T> q = Point<T>(f * (c.center.y - center.y) / d, f * (c.center.x - center.x) / d);
        return std::make_pair(p + q, p - q);
    }
    std::pair<Point<T>, Point<T>> getCrossPoints(const Point<T>& p) const {
        Point<T> a = p - center;
        T d = a.abs();
        T e = sqrt(square(d) - square(radius));
        Point<T> p = center + a * (radius / d);
        Point<T> q = Point<T>(e * (p.y - center.y) / d, e * (p.x - center.x) / d);
        return std::make_pair(p + q, p - q);
    }
    std::pair<Point<T>, Point<T>> getCrossPoints(const Line<T>& p) const {
        Point<T> a = p.b - p.a;
        Point<T> b = p.a - center;
        T A = a.dot(a);
        T B = a.dot(b);
        T C = b.dot(b) - square(radius);
        T D = B * B - A * C;
        if (D < 0.0) return std::make_pair(Point<T>(0, 0), Point<T>(0, 0));
        T t1 = (-B - sqrt(D)) / A;
        T t2 = (-B + sqrt(D)) / A;
        return std::make_pair(p.a + a * t1, p.a + a * t2);
    }
    std::pair<Point<T>, Point<T>> getCrossPoints(const Segment<T>& p) const {
        Point<T> a = p.b - p.a;
        Point<T> b = p.a - center;
        T A = a.dot(a);
        T B = a.dot(b);
        T C = b.dot(b) - square(radius);
        T D = B * B - A * C;
        if (D < 0.0) return std::make_pair(Point<T>(0, 0), Point<T>(0, 0));
        T t1 = (-B - sqrt(D)) / A;
        T t2 = (-B + sqrt(D)) / A;
        if (t1 < 0.0 && t2 < 0.0) return std::make_pair(Point<T>(0, 0), Point<T>(0, 0));
        if (t1 > 1.0 && t2 > 1.0) return std::make_pair(Point<T>(0, 0), Point<T>(0, 0));
        if (t1 < 0.0) t1 = 0.0;
        if (t1 > 1.0) t1 = 1.0;
        if (t2 < 0.0) t2 = 0.0;
        if (t2 > 1.0) t2 = 1.0;
        return std::make_pair(p.a + a * t1, p.a + a * t2);
    }
    std::pair<Point<T>, Point<T>> getTangentPoints(const Point<T>& p) const {
        Point<T> a = p - center;
        T d = a.abs();
        T e = sqrt(square(d) - square(radius));
        Point<T> p = center + a * (radius / d);
        Point<T> q = Point<T>(e * (p.y - center.y) / d, e * (p.x - center.x) / d);
        return std::make_pair(p + q, p - q);
    }
    std::pair<Point<T>, Point<T>> getTangentPoints(const Circle<T>& c) const {
        Point<T> a = c.center - center;
        T d = a.abs();
        T e = sqrt(square(d) - square(radius - c.radius));
        Point<T> p = center + a * (radius / d);
        Point<T> q = Point<T>(e * (c.center.y - center.y) / d, e * (c.center.x - center.x) / d);
        return std::make_pair(p + q, p - q);
    }
    std::pair<Point<T>, Point<T>> getTangentPoints(const Segment<T>& s) const {
        Circle<T> c1 = Circle<T>(s.a, radius);
        Circle<T> c2 = Circle<T>(s.b, radius);
        std::pair<Point<T>, Point<T>> p1 = getCrossPoints(c1);
        std::pair<Point<T>, Point<T>> p2 = getCrossPoints(c2);
        if (p1.first == p2.first) return std::make_pair(p1.first, p1.second);
        if (p1.first == p2.second) return std::make_pair(p1.first, p1.second);
        if (p1.second == p2.first) return std::make_pair(p1.second, p1.first);
        if (p1.second == p2.second) return std::make_pair(p1.second, p1.first);
        return std::make_pair(Point<T>(0, 0), Point<T>(0, 0));
    }
    friend std::ostream& operator<<(std::ostream& os, const Circle<T>& c) {
        os << "Circle(center=" << c.center << ", radius=" << c.radius << ")";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Circle<T>& c) {
        is >> c.center >> c.radius;
        return is;
    }
};

}


#endif // FLEURS_CIRCLE_HPP