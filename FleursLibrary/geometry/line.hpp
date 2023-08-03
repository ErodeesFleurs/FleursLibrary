#ifndef FLEURS_LINE_HPP
#define FLEURS_LINE_HPP 1

#include<FleursLibrary/geometry/point>

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

#endif // FLEURS_LINE_HPP