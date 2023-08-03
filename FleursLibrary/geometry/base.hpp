#ifndef FLEURS_BASE_HPP
#define FLEURS_BASE_HPP 1

#include <math.h>
namespace fleurs {
    using Real = double; // Change it to long double if you need more precision

    const Real EPS = 1e-9;
    const Real PI = acos(-1.0);

    inline bool equals(Real a, Real b) {
        return fabs(a - b) < EPS;
    }
    inline Real toDegree(Real rad) {
        return rad * 180.0 / PI;
    }
    inline Real toRadian(Real deg) {
        return deg * PI / 180.0;
    }
    inline Real square(Real x) {
        return x * x;
    }
    inline Real cube(Real x) {
        return x * x * x;
    }
    
}
#endif // FLEURS_BASE_HPP