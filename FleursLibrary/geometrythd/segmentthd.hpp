#ifndef FLEURS_SEGMENT_TRD_HPP
#define FLEURS_SEGMENT_TRD_HPP 1

#include<FleursLibrary/geometrythd/segmentthd.hpp>

namespace fleurs {

template <typename T>
struct segment3d {
    Point3d<T> a, b;

    segment3d() = default;
    segment3d(Point3d<T> a, Point3d<T> b) : a(a), b(b) {}
    segment3d(const segment3d<T>& l) : a(l.a), b(l.b) {}
    segment3d(T A, T B, T C) {
        if (equals(A, 0)) {
            a = Point3d<T>(0, -C / B);
            b = Point3d<T>(1, -C / B);
        } else if (equals(B, 0)) {
            a = Point3d<T>(-C / A, 0);
            b = Point3d<T>(-C / A, 1);
        } else {
            a = Point3d<T>(0, -C / B);
            b = Point3d<T>(1, -(A + C) / B);
        }
    }      
    segment3d operator-(void) const { return segment3d(-a, -b);}
    segment3d<T>& operator=(const segment3d<T>& l) { a = l.a;b = l.b;return *this;}
    bool operator==(const segment3d<T>& l) const { return equals(a, l.a) && equals(b, l.b); }
    bool operator!=(const segment3d<T>& l) const { return !equals(a, l.a) || !equals(b, l.b); }
    bool operator<(const segment3d<T>& l) const { return a < l.a || (a == l.a && b < l.b); }
    bool operator>(const segment3d<T>& l) const { return a > l.a || (a == l.a && b > l.b); }
    bool operator<=(const segment3d<T>& l) const { return a <= l.a || (a == l.a && b <= l.b); }
    bool operator>=(const segment3d<T>& l) const { return a >= l.a || (a == l.a && b >= l.b); }
    T length(void) const { return (b - a).length();}
    T distance(const Point3d<T>& p) const {
        if (dot(b - a, p - a) < 0) return (p - a).length();
        if (dot(a - b, p - b) < 0) return (p - b).length();
        return distance(p, *this);
    }
    Point3d<T> projection(const Point3d<T>& p) const {
        Point3d<T> base = b - a;
        return a + base * (dot(p - a, base) / base.norm());
    }
    Point3d<T> reflection(const Point3d<T>& p) const {
        return p + (projection(p) - p) * 2;
    }
};

} // namespace fleurs

#endif // FLEURS_SEGMENT_TRD_HPP