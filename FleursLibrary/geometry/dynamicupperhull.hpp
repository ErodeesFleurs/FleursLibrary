#ifndef FLEURS_DYNAMICUPPERHULL_HPP
#define FLEURS_DYNAMICUPPERHULL_HPP 1

#include <FleursLibrary/geometry/point>
#include <set>

namespace fleurs {

template <typename T> struct Dynamicupperhull {
  std::set<Point<T>> points;

  Dynamicupperhull() = default;
  Dynamicupperhull(const std::set<Point<T>> &points) : points(points) {}

  auto Prev(auto it) const {
    return (it == points.begin()) ? points.end() : std::prev(it);
  }

  auto Next(auto it) const {
    return (std::next(it) == points.end()) ? points.begin() : std::next(it);
  }
  bool isInside(const Point<T> &p) const {
    if (points.size() < 3)
      return false;
    auto it = points.lower_bound(p);
    it = (it == points.end()) ? points.begin() : it;
    return (p - (*Prev(it))).cross((*it) - (*Prev(it))) < EPS;
  }
  void addPoint(const Point<T> &p) {
    if (isInside(p))
      return;
    auto it = points.lower_bound(p);
    it = (it == points.end()) ? points.begin() : it;

    while (points.size() >= 2 &&
           (p - (*Prev(it))).cross((*it) - (*Prev(it))) > EPS) {
      it = points.erase(it);
      it = (it == points.end()) ? points.begin() : it;
    }
    points.insert(p);
  }
  void erasePoint(const Point<T> &p) {
    if (!isInside(p))
      return;
    auto it = points.lower_bound(p);
    it = (it == points.end()) ? points.begin() : it;

    while (points.size() >= 2 &&
           (p - (*Prev(it))).cross((*it) - (*Prev(it))) < -EPS) {
      it = points.erase(it);
      it = (it == points.end()) ? points.begin() : it;
    }
    points.erase(it);
  }
};

} // namespace fleurs

#endif // FLEURS_DYNAMICUPPERHULL_HPP
