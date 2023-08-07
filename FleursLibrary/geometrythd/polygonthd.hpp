#ifndef FLEURS_POLYGON_TRD_HPP
#define FLEURS_POLYGON_TRD_HPP 1

#include <vector>
#include <FleursLibrary/geometrythd/segmentthd.hpp>

namespace fleurs {
    template <typename T>
    struct Polygon3d {
        std::vector<Point3d<T>> points;
        Polygon3d() = default;
        Polygon3d(const std::vector<Point3d<T>>& points) : points(points) {}
        Polygon3d(const Polygon3d<T>& p) : points(p.points) {}
        Polygon3d<T>& operator=(const Polygon3d<T>& p) { points = p.points; return *this; }
        Point3d<T>& operator[](int i) { return points[i]; }
        const Point3d<T>& operator[](int i) const { return points[i]; }
        size_t size() const { return points.size(); }
    };
}

#endif // FLEURS_POLYGON_TRD_HPP