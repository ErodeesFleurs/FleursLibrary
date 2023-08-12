#ifndef FLEURS_LINE_TRD_HPP
#define FLEURS_LINE_TRD_HPP 1

#include <FleursLibrary/geometrythd/pointthd.hpp>

namespace fleurs {

template <typename T> struct Line3d {
  Point3d<T> a, b;

  Line3d() = default;
  Line3d(Point3d<T> a, Point3d<T> b) : a(a), b(b) {}
  Line3d(T A, T B, T C) {
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
  Line3d operator-(void) const { return Line3d(-a, -b); }
  Line3d<T> &operator=(const Line3d<T> &l) {
    a = l.a;
    b = l.b;
    return *this;
  }
  bool operator==(const Line3d<T> &l) const {
    return equals(a, l.a) && equals(b, l.b);
  }
  bool operator!=(const Line3d<T> &l) const {
    return !equals(a, l.a) || !equals(b, l.b);
  }
  bool operator<(const Line3d<T> &l) const {
    return equals(a, l.a) ? b < l.b : a < l.a;
  }
  bool operator>(const Line3d<T> &l) const {
    return equals(a, l.a) ? b > l.b : a > l.a;
  }
  bool operator<=(const Line3d<T> &l) const {
    return equals(a, l.a) ? b <= l.b : a <= l.a;
  }
  bool operator>=(const Line3d<T> &l) const {
    return equals(a, l.a) ? b >= l.b : a >= l.a;
  }

  T distance(const Point3d<T> &p) const {
    return std::abs((b - a).cross(p - a)) / length();
  }
  T distance(const Line3d<T> &l) const {
    return std::min(
        {distance(l.a), distance(l.b), l.distance(a), l.distance(b)});
  }
  bool isParallel(const Line3d<T> &l) const {
    return equals((b - a).cross(l.b - l.a), 0);
  }
  bool isOrthogonal(const Line3d<T> &l) const {
    return equals((b - a).dot(l.b - l.a), 0);
  }
  bool isIntersect(const Line3d<T> &l) const {
    return !is_parallel(l) || equals(distance(l), 0);
  }
  bool isIntersect(const Point3d<T> &p) const { return equals(distance(p), 0); }

  Point3d<T> projection(const Point3d<T> &p) const {
    return a + (b - a).dot(p - a) / length() * (b - a);
  }
  Point3d<T> reflection(const Point3d<T> &p) const {
    return 2 * projection(p) - p;
  }
  Point3d<T> intersection(const Line3d<T> &l) const {
    if (isParallel(l))
      return Point3d<T>(DBL_MAX, DBL_MAX);
    const Point3d<T> p = l.a, q = l.b;
    const T num = (q - p).cross(p - a);
    const T den = (q - p).cross(b - a);
    return a + (b - a) * num / den;
  }
};

} // namespace fleurs

#endif // FLEURS_LINE_TRD_HPP
