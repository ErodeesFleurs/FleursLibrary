/**
 * HELLO WORLD
 * Author: ErodeesFleurs
**/

#include<bits/stdc++.h>

#include<iostream>
#include<math.h>

namespace fleurs {
    using Real = long double; // Change it to long double if you need more precision

    const Real EPS = 1e-9;
    const Real PI = acos(-1.0);

    inline bool equals(Real a, Real b) {
        return fabs(a - b) < EPS;
    }
    inline Real toDegree(Real rad) {
        return rad * 180.0 / PI;
    }
    inline Real toRadian(Real deg) {
        return deg * PI / 180.0;
    }
    inline Real square(Real x) {
        return x * x;
    }
    inline Real cube(Real x) {
        return x * x * x;
    }
    
}

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

    Point<T> rotate(double theta) const {
        return Point<T>(std::cos(theta) * x - std::sin(theta) * y,
                        std::sin(theta) * x + std::cos(theta) * y);
    }
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


namespace fleurs {

template <typename T>
struct Line {
    Point<T> a, b;

    Line() = default;
    Line(Point<T> a, Point<T> b) : a(a), b(b) {}
    Line(std::pair<T, T> a, std::pair<T, T> b) : a(a), b(b) {}
    Line(std::pair<Point<T>, Point<T>> l) : a(l.first), b(l.second) {}
    Line(T ax, T ay, T bx, T by) : a(ax, ay), b(bx, by) {}
    Line(const Line<T>& l) : a(l.a), b(l.b) {}
    Line(T A, T B, T C) {
        if (equals(A, 0)) {
            a = Point<T>(0, -C / B);
            b = Point<T>(1, -C / B);
        } else if (equals(B, 0)) {
            a = Point<T>(-C / A, 0);
            b = Point<T>(-C / A, 1);
        } else {
            a = Point<T>(0, -C / B);
            b = Point<T>(1, -(A + C) / B);
        }
    }      
    Line operator-(void) const {
        return Line(-a, -b);
    }
    Line<T>& operator=(const Line<T>& l) {
        a = l.a;
        b = l.b;
        return *this;
    }
    Line<T>& operator=(std::pair<Point<T>, Point<T>> l) {
        a = l.first;
        b = l.second;
        return *this;
    }
    Line<T>& operator=(std::pair<T, T> l) {
        a = Point<T>(l.first, l.second);
        b = Point<T>(l.first, l.second);
        return *this;
    }
    bool operator==(const Line<T>& l) const {
        return equals(a, l.a) && equals(b, l.b);
    }
    bool operator!=(const Line<T>& l) const {
        return !equals(a, l.a) || !equals(b, l.b);
    }
    bool operator<(const Line<T>& l) const {
        return a < l.a || (a == l.a && b < l.b);
    }
    bool operator>(const Line<T>& l) const {
        return a > l.a || (a == l.a && b > l.b);
    }
    bool operator<=(const Line<T>& l) const {
        return a <= l.a || (a == l.a && b <= l.b);
    }
    bool operator>=(const Line<T>& l) const {
        return a >= l.a || (a == l.a && b >= l.b);
    }
    bool isParallel(const Line<T>& l) const {
        return equals((b - a).cross(l.b - l.a), 0);
    }
    bool isOrthogonal(const Line<T>& l) const {
        return equals((b - a).dot(l.b - l.a), 0);
    }
    bool isIntersection(const Line<T>& l) const {
        return !isParallel(l) || equals((b - a).cross(l.a - a), 0);
    }
    bool isIntersection(const Point<T>& p) const {
        return equals((b - a).cross(p - a), 0);
    }
    Point<T> projection(const Point<T>& p) const {
        Point<T> v = b - a;
        return a + v * (v.dot(p - a) / v.norm());
    }
    Point<T> reflection(const Point<T>& p) const {
        return p + (projection(p) - p) * 2;
    }
    Point<T> intersection(const Line<T>& l) const {
        Point<T> v = b - a, w = l.b - l.a;
        return a + v * ((l.a - a).cross(w) / v.cross(w));
    }
    T distance(const Point<T>& p) const {
        return (p - projection(p)).abs();
    }
    T distance(const Line<T>& l) const {
        return isIntersection(l) ? 0 : distance(l.a);
    }
    friend std::ostream& operator<<(std::ostream& os, const Line<T>& l) {
        return os << "(" << l.a << ", " << l.b << ")";
    }
    friend std::istream& operator>>(std::istream& is, Line<T>& l) {
        return is >> l.a >> l.b;
    }
};

} // namespace fleurs


namespace fleurs {

template <typename T>
struct Segment {
    Point<T> a, b;

    Segment() = default;
    Segment(Point<T> a, Point<T> b) : a(a), b(b) {}
    Segment(std::pair<T, T> a, std::pair<T, T> b) : a(a), b(b) {}
    Segment(std::pair<Point<T>, Point<T>> l) : a(l.first), b(l.second) {}
    Segment(T ax, T ay, T bx, T by) : a(ax, ay), b(bx, by) {}
    Segment(const Segment<T>& l) : a(l.a), b(l.b) {}
    Segment(T A, T B, T C) {
        if (equals(A, 0)) {
            a = Point<T>(0, -C / B);
            b = Point<T>(1, -C / B);
        } else if (equals(B, 0)) {
            a = Point<T>(-C / A, 0);
            b = Point<T>(-C / A, 1);
        } else {
            a = Point<T>(0, -C / B);
            b = Point<T>(1, -(A + C) / B);
        }
    }      
    Segment operator-(void) const {
        return Segment(-a, -b);
    }
    Segment<T>& operator=(const Segment<T>& l) {
        a = l.a;
        b = l.b;
        return *this;
    }
    Segment<T>& operator=(std::pair<Point<T>, Point<T>> l) {
        a = l.first;
        b = l.second;
        return *this;
    }
    Segment<T>& operator=(std::pair<T, T> l) {
        a = Point<T>(l.first, l.second);
        b = Point<T>(l.first, l.second);
        return *this;
    }
    bool operator==(const Segment<T>& l) const {
        return equals(a, l.a) && equals(b, l.b);
    }
    bool operator!=(const Segment<T>& l) const {
        return !equals(a, l.a) || !equals(b, l.b);
    }
    bool operator<(const Segment<T>& l) const {
        return a < l.a || (a == l.a && b < l.b);
    }
    bool operator>(const Segment<T>& l) const {
        return a > l.a || (a == l.a && b > l.b);
    }
    bool operator<=(const Segment<T>& l) const {
        return a <= l.a || (a == l.a && b <= l.b);
    }
    bool operator>=(const Segment<T>& l) const {
        return a >= l.a || (a == l.a && b >= l.b);
    }
    bool isParallel(const Segment<T>& l) const {
        return equals((b - a).cross(l.b - l.a), 0);
    }
    bool isOrthogonal(const Segment<T>& l) const {
        return equals((b - a).dot(l.b - l.a), 0);
    }
    bool isIntersect(const Segment<T>& l) const {
        return (b - a).cross(l.a - a) * (b - a).cross(l.b - a) < 0 &&
                (l.b - l.a).cross(a - l.a) * (l.b - l.a).cross(b - l.a) < 0;
    }
    bool isIntersect(const Line<T>& l) const {
        return equals((b - a).cross(l.a - a), 0) && (b - a).cross(l.b - a) * (b - a).cross(l.b - a) < 0;
    }
    bool isIntersect(const Point<T>& p) const {
        return equals((b - a).cross(p - a), 0) && (b - a).dot(p - a) > 0 && (a - b).dot(p - b) > 0;
    }
    bool include(const Point<T>& p) const {
        return equals((b - a).cross(p - a), 0) && (b - a).dot(p - a) > 0 && (a - b).dot(p - b) > 0;
    }
    bool include(const Segment<T>& l) const {
        return include(l.a) && include(l.b);
    }
    Point<T> projection(const Point<T>& p) const {
        return a + (b - a) * ((b - a).dot(p - a) / (b - a).norm());
    }
    Point<T> reflection(const Point<T>& p) const {
        return p + (projection(p) - p) * 2;
    }
    Point<T> intersection(const Segment<T>& l) const {
        Point<T> v = b - a, w = l.b - l.a;
        return a + v * ((l.a - a).cross(w) / v.cross(w));
    }
    Point<T> intersection(const Line<T>& l) const {
        Point<T> v = b - a;
        return a + v * ((l.a - a).cross(l.b - l.a) / v.cross(l.b - l.a));
    }
    T distance(const Point<T>& p) const {
        if ((p - a).dot(b - a) < 0) return (p - a).abs();
        if ((p - b).dot(a - b) < 0) return (p - b).abs();
        return std::abs((b - a).cross(p - a)) / (b - a).abs();
    }
    T distance(const Segment<T>& l) const {
        if (isIntersect(l)) return 0;
        return std::min({distance(l.a), distance(l.b), l.distance(a), l.distance(b)});
    }
    T distance(const Line<T>& l) const {
        if (isIntersect(l)) return 0;
        return std::min(l.distance(a), l.distance(b));
    }
    T length(void) const {
        return (b - a).abs();
    }
    T angle(const Segment<T>& l) const {
        return std::acos((b - a).dot(l.b - l.a) / ((b - a).abs() * (l.b - l.a).abs()));
    }
    T angle(const Line<T>& l) const {
        return std::acos((b - a).dot(l.b - l.a) / ((b - a).abs() * (l.b - l.a).abs()));
    }
    Point<T> vector(void) const {
        return b - a;
    }
    Point<T> unitVector(void) const {
        return (b - a) / (b - a).abs();
    }
    Point<T> normalVector(void) const {
        return (b - a).normal();
    }
    Point<T> unitNormalVector(void) const {
        return (b - a).normal() / (b - a).abs();
    }
    Point<T> center(void) const {
        return (a + b) / 2;
    }
    friend std::ostream& operator<<(std::ostream& os, const Segment<T>& l) {
        return os << l.a << " -> " << l.b;
    }
    friend std::istream& operator>>(std::istream& is, Segment<T>& l) {
        return is >> l.a >> l.b;
    }
};

}



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
    bool isIntersect(const Circle<T>& c) const {
        return !contains(c) && !c.contains(*this) && (center - c.center).abs() <= radius + c.radius;
    }
    bool isIntersect(const Point<T>& p) const {
        return equals((p - center).abs(), radius);
    }
    bool isIntersect(const Segment<T>& s) const {
        return (s.a - center).abs() <= radius || (s.b - center).abs() <= radius || (center - s.a).abs() <= radius && (center - s.b).abs() <= radius && s.distance(center) <= radius;
    }
    bool isIntersect(const Line<T>& l) const {
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
        if (!isIntersect(p)) return std::make_pair(Point<T>(0, 0), Point<T>(0, 0));
        Point<T> a = p - center;
        T b = sqrt(square(radius) - square(a.abs()));
        Point<T> p1 = center + a * (b / a.abs());
        Point<T> p2 = center + a * (-b / a.abs());
        return std::make_pair(p1, p2);
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
        if (!isIntersect(p)) return std::make_pair(Point<T>(0, 0), Point<T>(0, 0));
        Point<T> a = p - center;
        T b = sqrt(square(radius) - square(a.abs()));
        Point<T> p1 = center + a * (b / a.abs());
        Point<T> p2 = center + a * (-b / a.abs());
        return std::make_pair(p1, p2);
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



namespace fleurs {

template <typename T>
struct Polygon{
    std::vector<Point<T>> points;

    Polygon() = default;
    Polygon(const std::vector<Point<T>>& points) : points(points) {}
    Polygon(const Polygon<T>& p) : points(p.points) {}

    size_t size() const {
        return points.size();
    }
    Polygon<T>& operator=(const Polygon<T>& p) {
        points = p.points;
        return *this;
    }
    Point<T>& operator[](size_t i) {
        return points[i];
    }
    const Point<T>& operator[](size_t i) const {
        return points[i];
    }
    bool operator==(const Polygon<T>& p) const {
        return points == p.points;
    }
    bool operator!=(const Polygon<T>& p) const {
        return points != p.points;
    }
    T area() const {
        T res = 0;
        for (size_t i = 0; i < points.size(); ++i) {
            res += points[i].cross(points[(i + 1) % points.size()]);
        }
        return res / 2;
    }
    bool isConvex() const {
        bool res = true;
        for (size_t i = 0; i < points.size(); ++i) {
            Point<T> a = points[i] - points[(i + 1) % points.size()];
            Point<T> b = points[(i + 2) % points.size()] - points[(i + 1) % points.size()];
            res &= a.cross(b) <= 0;
        }
        return res;
    }
    bool isSimple() const {
        for (size_t i = 0; i < points.size(); ++i) {
            Segment<T> s1(points[i], points[(i + 1) % points.size()]);
            for (size_t j = i + 1; j < points.size(); ++j) {
                Segment<T> s2(points[j], points[(j + 1) % points.size()]);
                if (s1.intersect(s2)) {
                    return false;
                }
            }
        }
        return true;
    }
    bool isInside(const Point<T>& p) const {
        bool res = false;
        for (size_t i = 0; i < points.size(); ++i) {
            Point<T> a = points[i] - p;
            Point<T> b = points[(i + 1) % points.size()] - p;
            if (a.y > b.y) {
                std::swap(a, b);
            }
            if (a.y <= 0 && 0 < b.y && a.cross(b) < 0) {
                res = !res;
            }
            if (a.cross(b) == 0 && a.dot(b) <= 0) {
                return true;
            }
        }
        return res;
    }
    bool isOnEdge(const Point<T>& p) const {
        for (size_t i = 0; i < points.size(); ++i) {
            Segment<T> s(points[i], points[(i + 1) % points.size()]);
            if (s.isOnSegment(p)) {
                return true;
            }
        }
        return false;
    }
    bool isOnPolygon(const Point<T>& p) const {
        return isInside(p) || isOnEdge(p);
    }
    Point<T> centroid() const {
        Point<T> res;
        T a = 0;
        for (size_t i = 0; i < points.size(); ++i) {
            T tmp = points[i].cross(points[(i + 1) % points.size()]);
            res += (points[i] + points[(i + 1) % points.size()]) * tmp;
            a += tmp;
        }
        return res / (3 * a);
    }
    bool intersect(const Segment<T>& s) const {
        for (size_t i = 0; i < points.size(); ++i) {
            Segment<T> t(points[i], points[(i + 1) % points.size()]);
            if (t.intersect(s)) {
                return true;
            }
        }
        return false;
    }
    bool intersect(const Line<T>& l) const {
        for (size_t i = 0; i < points.size(); ++i) {
            Segment<T> s(points[i], points[(i + 1) % points.size()]);
            if (s.intersect(l)) {
                return true;
            }
        }
        return false;
    }
    bool intersect(const Circle<T>& c) const {
        for (size_t i = 0; i < points.size(); ++i) {
            Segment<T> s(points[i], points[(i + 1) % points.size()]);
            if (s.intersect(c)) {
                return true;
            }
        }
        return false;
    }
    Polygon<T> convexHull() const {
        Polygon<T> res;
        std::vector<Point<T>> ps = points;
        std::sort(ps.begin(), ps.end());
        std::vector<Point<T>> qs;
        for (size_t i = 0; i < ps.size(); ++i) {
            while (qs.size() > 1 && (qs[qs.size() - 1] - qs[qs.size() - 2]).cross(ps[i] - qs[qs.size() - 1]) <= 0) {
                qs.pop_back();
            }
            qs.push_back(ps[i]);
        }
        int limit = qs.size();
        for (size_t i = ps.size() - 1; i > 0; --i) {
            while (qs.size() > limit && (qs[qs.size() - 1] - qs[qs.size() - 2]).cross(ps[i - 1] - qs[qs.size() - 1]) <= 0) {
                qs.pop_back();
            }
            qs.push_back(ps[i - 1]);
        }
        qs.pop_back();
        res.points = qs;
        return res;
    }
    Polygon<T> convexCut(const Segment<T>& s) const {
        Polygon<T> res;
        for (size_t i = 0; i < points.size(); ++i) {
            Point<T> a = points[i];
            Point<T> b = points[(i + 1) % points.size()];
            if (s.projection(a).cross(s.projection(b)) < 0) {
                res.points.push_back(s.crossPoint(Segment<T>(a, b)));
            }
            if (s.projection(a).cross(s.projection(b)) <= 0) {
                res.points.push_back(b);
            }
        }
        return res;
    }
    std::vector<Polygon<T>> convexCut(const Polygon<T>& p) const {
        Polygon<T> q = *this;
        std::vector<Polygon<T>> res;
        for (size_t i = 0; i < p.points.size(); ++i) {
            Segment<T> s(p.points[i], p.points[(i + 1) % p.points.size()]);
            res.push_back(q.convexCut(s));
            q = q.convexCut(s);
        }
        return res;
    }
    Circle<T> minEnclosingCircle() const {
        std::vector<Point<T>> ps = points;
        std::random_shuffle(ps.begin(), ps.end());
        Circle<T> c(ps[0], 0);
        for (size_t i = 1; i < ps.size(); ++i) {
            if (!c.isInside(ps[i])) {
                c = Circle<T>(ps[i], 0);
                for (size_t j = 0; j < i; ++j) {
                    if (!c.isInside(ps[j])) {
                        c = Circle<T>((ps[i] + ps[j]) / 2, (ps[i] - ps[j]).norm() / 2);
                        for (size_t k = 0; k < j; ++k) {
                            if (!c.isInside(ps[k])) {
                                c = Circle<T>(ps[i], ps[j], ps[k]);
                            }
                        }
                    }
                }
            }
        }
        return c;
    }
    friend std::ostream& operator<<(std::ostream& os, const Polygon<T>& p) {
        os << "[";
        for (size_t i = 0; i < p.points.size(); ++i) {
            os << p.points[i];
            if (i + 1 != p.points.size()) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Polygon<T>& p) {
        size_t n;
        is >> n;
        p.points.resize(n);
        for (size_t i = 0; i < n; ++i) {
            is >> p.points[i];
        }
        return is;
    }
};


}


namespace fleurs{
template <typename T>
T rotcaliper(const Polygon<T>& p) {
    T res = 1e10;
    int n = p.size();
    for(int i = 0, k = 1; i < n; i++) {
        while((p[(i + 1) % n] - p[i]).cross(p[k] - p[i]) < (p[(i + 1) % n] - p[i]).cross(p[(k + 1) % n] - p[i])) {
            k = (k + 1) % n;
        }
        #ifndef ONLINE_JUDGE
            std::cout << "p: " << i << " " << k << std::endl;
        #endif
        res = std::min(res, fleurs::Line<T>(p[i], p[(i + 1) % n]).distance(p[k]));
        #ifndef ONLINE_JUDGE
            std::cout << "r: " << res << std::endl;
        #endif
    }
    return res;
}
}

template <typename T, typename F> 
T operator|(const fleurs::Polygon<T>& a, const F b) {
    T res = b(a);
    return res;
}

void solve() {
    int n = 0;
    fleurs::Polygon<fleurs::Real> p;
    std::cin >> p;
    fleurs::Polygon<fleurs::Real> ch = p.convexHull();
    std::function<fleurs::Real (fleurs::Polygon<fleurs::Real>)> f = fleurs::rotcaliper<fleurs::Real>;
    std::cout << std::fixed << std::setprecision(2) << (ch | f) << std::endl;
}

auto main() -> signed {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    for(int __case = 1; __case <= t; __case++) {
        solve();
    }
    return 0;
}