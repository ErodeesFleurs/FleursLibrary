#ifndef FLEURS_LINE_HPP
#define FLEURS_LINE_HPP

#include <FleursLibrary/geometry/point>

namespace fleurs {

template <typename T>
struct Line {
    Point<T> a, b;

    Line() = default;
    Line(Point<T> a, Point<T> b) : a(a), b(b) {}

    Line operator-() const { return Line(-a, -b); }

    bool operator==(const Line<T>& l) const { return a == l.a && b == l.b; }
    bool operator!=(const Line<T>& l) const { return !(*this == l); }

    bool isParallel(const Line<T>& l) const { return (b - a).cross(l.b - l.a) == 0; }
    bool isOrthogonal(const Line<T>& l) const { return (b - a).dot(l.b - l.a) == 0; }
    bool isIntersection(const Line<T>& l) const { return !isParallel(l) || (b - a).cross(l.a - a) == 0; }
    bool isIntersection(const Point<T>& p) const { return (b - a).cross(p - a) == 0; }

    Point<T> projection(const Point<T>& p) const {
        Point<T> v = b - a;
        return a + v * (v.dot(p - a) / v.norm());
    }
    Point<T> reflection(const Point<T>& p) const { return p + (projection(p) - p) * 2; }
    Point<T> intersection(const Line<T>& l) const {
        Point<T> v = b - a, w = l.b - l.a;
        return a + v * ((l.a - a).cross(w) / v.cross(w));
    }

    T distance(const Point<T>& p) const { return (p - projection(p)).abs(); }
    T distance(const Line<T>& l) const { return isIntersection(l) ? 0 : distance(l.a); }

    friend std::ostream& operator<<(std::ostream& os, const Line<T>& l) { return os << "(" << l.a << ", " << l.b << ")"; }
    friend std::istream& operator>>(std::istream& is, Line<T>& l) { return is >> l.a >> l.b; }
};

} // namespace fleurs

#endif // FLEURS_LINE_HPP

