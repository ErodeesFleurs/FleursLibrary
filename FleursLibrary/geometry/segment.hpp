#ifndef FLEURS_SEGMENT_HPP
#define FLEURS_SEGMENT_HPP

#include <FleursLibrary/geometry/line>

namespace fleurs {

template <typename T> struct Segment {
  Point<T> a, b;

  Segment() = default;
  Segment(Point<T> a, Point<T> b) : a(a), b(b) {}

  bool operator==(const Segment<T> &l) const { return a == l.a && b == l.b; }
  bool operator!=(const Segment<T> &l) const { return !(*this == l); }

  bool isParallel(const Segment<T> &l) const {
    return (b - a).cross(l.b - l.a) == 0;
  }

  bool isIntersect(const Segment<T> &l) const {
    return (b - a).cross(l.a - a) * (b - a).cross(l.b - a) < 0 &&
           (l.b - l.a).cross(a - l.a) * (l.b - l.a).cross(b - l.a) < 0;
  }

  bool isIntersect(const Point<T> &p) const {
    return (b - a).cross(p - a) == 0 && (b - a).dot(p - a) > 0 &&
           (a - b).dot(p - b) > 0;
  }

  bool isIntersect(const Line<T> &l) const {
    auto cross1 = (l.b - l.a).cross(a - l.a);
    auto cross2 = (l.b - l.a).cross(b - l.a);
    return cross1 * cross2 <= 0;
  }

  Point<T> intersection(const Line<T> &l) const {
    Point<T> v = b - a;
    return a + v * ((l.a - a).cross(l.b - l.a) / v.cross(l.b - l.a));
  }

  Point<T> projection(const Point<T> &p) const {
    return a + (b - a) * ((b - a).dot(p - a) / (b - a).norm());
  }

  Point<T> reflection(const Point<T> &p) const {
    return p + (projection(p) - p) * 2;
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

  T length() const { return (b - a).abs(); }

  Point<T> center() const { return (a + b) / 2; }

  friend std::ostream &operator<<(std::ostream &os, const Segment<T> &l) {
    return os << l.a << " -> " << l.b;
  }

  friend std::istream &operator>>(std::istream &is, Segment<T> &l) {
    return is >> l.a >> l.b;
  }
};

} // namespace fleurs

#endif // FLEURS_SEGMENT_HPP

