#ifndef FLEURS_SEGMENT_HPP
#define FLEURS_SEGMENT_HPP 1

#include <FleursLibrary/geometry/line>

namespace fleurs {

template <typename T> struct Segment {
  Point<T> a, b;

  Segment() = default;
  Segment(Point<T> a, Point<T> b) : a(a), b(b) {}
  Segment(std::pair<T, T> a, std::pair<T, T> b) : a(a), b(b) {}
  Segment(std::pair<Point<T>, Point<T>> l) : a(l.first), b(l.second) {}
  Segment(T ax, T ay, T bx, T by) : a(ax, ay), b(bx, by) {}
  Segment(const Segment<T> &l) : a(l.a), b(l.b) {}
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
  Segment operator-(void) const { return Segment(-a, -b); }
  Segment<T> &operator=(const Segment<T> &l) {
    a = l.a;
    b = l.b;
    return *this;
  }
  Segment<T> &operator=(std::pair<Point<T>, Point<T>> l) {
    a = l.first;
    b = l.second;
    return *this;
  }
  Segment<T> &operator=(std::pair<T, T> l) {
    a = Point<T>(l.first, l.second);
    b = Point<T>(l.first, l.second);
    return *this;
  }
  bool operator==(const Segment<T> &l) const {
    return equals(a, l.a) && equals(b, l.b);
  }
  bool operator!=(const Segment<T> &l) const {
    return !equals(a, l.a) || !equals(b, l.b);
  }
  bool operator<(const Segment<T> &l) const {
    return a < l.a || (a == l.a && b < l.b);
  }
  bool operator>(const Segment<T> &l) const {
    return a > l.a || (a == l.a && b > l.b);
  }
  bool operator<=(const Segment<T> &l) const {
    return a <= l.a || (a == l.a && b <= l.b);
  }
  bool operator>=(const Segment<T> &l) const {
    return a >= l.a || (a == l.a && b >= l.b);
  }
  bool isParallel(const Segment<T> &l) const {
    return equals((b - a).cross(l.b - l.a), 0);
  }
  bool isOrthogonal(const Segment<T> &l) const {
    return equals((b - a).dot(l.b - l.a), 0);
  }
  bool isIntersect(const Segment<T> &l) const {
    return (b - a).cross(l.a - a) * (b - a).cross(l.b - a) < 0 &&
           (l.b - l.a).cross(a - l.a) * (l.b - l.a).cross(b - l.a) < 0;
  }
  bool isIntersect(const Line<T> &l) const {
    return equals((b - a).cross(l.a - a), 0) &&
           (b - a).cross(l.b - a) * (b - a).cross(l.b - a) < 0;
  }
  bool isIntersect(const Point<T> &p) const {
    return equals((b - a).cross(p - a), 0) && (b - a).dot(p - a) > 0 &&
           (a - b).dot(p - b) > 0;
  }
  bool include(const Point<T> &p) const {
    return equals((b - a).cross(p - a), 0) && (b - a).dot(p - a) > 0 &&
           (a - b).dot(p - b) > 0;
  }
  bool include(const Segment<T> &l) const {
    return include(l.a) && include(l.b);
  }
  Point<T> projection(const Point<T> &p) const {
    return a + (b - a) * ((b - a).dot(p - a) / (b - a).norm());
  }
  Point<T> reflection(const Point<T> &p) const {
    return p + (projection(p) - p) * 2;
  }
  Point<T> intersection(const Segment<T> &l) const {
    Point<T> v = b - a, w = l.b - l.a;
    return a + v * ((l.a - a).cross(w) / v.cross(w));
  }
  Point<T> intersection(const Line<T> &l) const {
    Point<T> v = b - a;
    return a + v * ((l.a - a).cross(l.b - l.a) / v.cross(l.b - l.a));
  }
  T distance(const Point<T> &p) const {
    if ((p - a).dot(b - a) < 0)
      return (p - a).abs();
    if ((p - b).dot(a - b) < 0)
      return (p - b).abs();
    return std::abs((b - a).cross(p - a)) / (b - a).abs();
  }
  T distance(const Segment<T> &l) const {
    if (isIntersect(l))
      return 0;
    return std::min(
        {distance(l.a), distance(l.b), l.distance(a), l.distance(b)});
  }
  T distance(const Line<T> &l) const {
    if (isIntersect(l))
      return 0;
    return std::min(l.distance(a), l.distance(b));
  }
  T length(void) const { return (b - a).abs(); }
  T angle(const Segment<T> &l) const {
    return std::acos((b - a).dot(l.b - l.a) /
                     ((b - a).abs() * (l.b - l.a).abs()));
  }
  T angle(const Line<T> &l) const {
    return std::acos((b - a).dot(l.b - l.a) /
                     ((b - a).abs() * (l.b - l.a).abs()));
  }
  Point<T> vector(void) const { return b - a; }
  Point<T> unitVector(void) const { return (b - a) / (b - a).abs(); }
  Point<T> normalVector(void) const { return (b - a).normal(); }
  Point<T> unitNormalVector(void) const {
    return (b - a).normal() / (b - a).abs();
  }
  Point<T> center(void) const { return (a + b) / 2; }
  friend std::ostream &operator<<(std::ostream &os, const Segment<T> &l) {
    return os << l.a << " -> " << l.b;
  }
  friend std::istream &operator>>(std::istream &is, Segment<T> &l) {
    return is >> l.a >> l.b;
  }
};

} // namespace fleurs

#endif // FLEURS_SEGMENT_HPP
