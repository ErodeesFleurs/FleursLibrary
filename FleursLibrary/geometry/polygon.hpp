#ifndef FLEURS_POLYGON_HPP
#define FLEURS_POLYGON_HPP 1

#include <FleursLibrary/geometry/circle>
#include <algorithm>
#include <random>
#include <vector>

namespace fleurs {

template <typename T> struct Polygon {
  std::vector<Point<T>> points;

  Polygon() = default;
  Polygon(const std::vector<Point<T>> &points) : points(points) {}
  Polygon(const Polygon<T> &p) : points(p.points) {}

  size_t size() const { return points.size(); }
  Polygon<T> &operator=(const Polygon<T> &p) {
    points = p.points;
    return *this;
  }
  Point<T> &operator[](size_t i) { return points[i]; }
  const Point<T> &operator[](size_t i) const { return points[i]; }
  bool operator==(const Polygon<T> &p) const { return points == p.points; }
  bool operator!=(const Polygon<T> &p) const { return points != p.points; }
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
      Point<T> b =
          points[(i + 2) % points.size()] - points[(i + 1) % points.size()];
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
  bool isInside(const Point<T> &p) const {
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
  bool isOnEdge(const Point<T> &p) const {
    for (size_t i = 0; i < points.size(); ++i) {
      Segment<T> s(points[i], points[(i + 1) % points.size()]);
      if (s.isOnSegment(p)) {
        return true;
      }
    }
    return false;
  }
  bool isOnPolygon(const Point<T> &p) const {
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
  bool intersect(const Segment<T> &s) const {
    for (size_t i = 0; i < points.size(); ++i) {
      Segment<T> t(points[i], points[(i + 1) % points.size()]);
      if (t.intersect(s)) {
        return true;
      }
    }
    return false;
  }
  bool intersect(const Line<T> &l) const {
    for (size_t i = 0; i < points.size(); ++i) {
      Segment<T> s(points[i], points[(i + 1) % points.size()]);
      if (s.intersect(l)) {
        return true;
      }
    }
    return false;
  }
  bool intersect(const Circle<T> &c) const {
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
      while (qs.size() > 1 && (qs[qs.size() - 1] - qs[qs.size() - 2])
                                      .cross(ps[i] - qs[qs.size() - 1]) <= 0) {
        qs.pop_back();
      }
      qs.push_back(ps[i]);
    }
    int limit = qs.size();
    for (size_t i = ps.size() - 1; i > 0; --i) {
      while (qs.size() > limit &&
             (qs[qs.size() - 1] - qs[qs.size() - 2])
                     .cross(ps[i - 1] - qs[qs.size() - 1]) <= 0) {
        qs.pop_back();
      }
      qs.push_back(ps[i - 1]);
    }
    qs.pop_back();
    res.points = qs;
    return res;
  }
  Polygon<T> convexCut(const Segment<T> &s) const {
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
  std::vector<Polygon<T>> convexCut(const Polygon<T> &p) const {
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
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ps.begin(), ps.end(), rd);
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
  friend std::ostream &operator<<(std::ostream &os, const Polygon<T> &p) {
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
  friend std::istream &operator>>(std::istream &is, Polygon<T> &p) {
    size_t n;
    is >> n;
    p.points.resize(n);
    for (size_t i = 0; i < n; ++i) {
      is >> p.points[i];
    }
    return is;
  }
};

} // namespace fleurs

#endif // FLEURS_POLYGON_HPP
