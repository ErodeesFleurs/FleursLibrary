#ifndef FLEURS_DYNAMICUPPERHULL_HPP
#define FLEURS_DYNAMICUPPERHULL_HPP 1

#include <FleursLibrary/geometry/point>
#include <set>

namespace fleurs {

template <typename T> struct Dynamicupperhull {
  std::set<Point<T>> points;

  Dynamicupperhull() = default;
  Dynamicupperhull(const std::set<Point<T>> &points) : points(points) {}
  Dynamicupperhull(const Dynamicupperhull<T> &p) : points(p.points) {}

  std::set<Point<T>>::iterator Prev(std::set<Point<T>>::iterator it) {
    if (it == points.begin()) {
      return points.end();
    }
    return --it;
  }
  std::set<Point<T>>::iterator Next(std::set<Point<T>>::iterator it) {
    ++it;
    if (it == points.end()) {
      return points.begin();
    }
    return it;
  }
  bool isInside(Point<T> p) {
    if (points.size() < 3)
      return false;
    auto it = points.lower_bound(p);
    if (it == points.end())
      it = points.begin();
    if (it == points.begin())
      return false;
    return (p - (*Prev(it))).cross((*it) - (*Prev(it))) < EPS;
  }
  void addPoint(Point<T> p) {
    if (isInside(p))
      return;
    auto it = points.lower_bound(p);
    if (it == points.end())
      it = points.begin();
    while (points.size() >= 2 &&
           (p - (*Prev(it))).cross((*it) - (*Prev(it))) > EPS) {
      points.erase(it);
      it = points.lower_bound(p);
      if (it == points.end())
        it = points.begin();
    }
    points.insert(p);
  }
  void erasePoint(Point<T> p) {
    if (!isInside(p))
      return;
    auto it = points.lower_bound(p);
    if (it == points.end())
      it = points.begin();
    while (points.size() >= 2 &&
           (p - (*Prev(it))).cross((*it) - (*Prev(it))) < -EPS) {
      points.erase(it);
      it = points.lower_bound(p);
      if (it == points.end())
        it = points.begin();
    }
    points.erase(it);
  }
};

} // namespace fleurs

#endif // FLEURS_DYNAMICUPPERHULL_HPP
