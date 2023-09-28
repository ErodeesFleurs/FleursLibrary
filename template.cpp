/**
 * HELLO WORLD
 * Author: ErodeesFleurs
**/

#include<bits/stdc++.h>
#include<FleursLibrary/geometry/polygon>

namespace fleurs{
template <typename T>
T rotcaliper(const Polygon<T>& p) {
    T res = 1e10;
    int n = p.size();
    for(int i = 0, k = 1; i < n; i++) {
        while((p[(i + 1) % n] - p[i]).cross(p[k] - p[i]) < (p[(i + 1) % n] - p[i]).cross(p[(k + 1) % n] - p[i])) {
            k = (k + 1) % n;
        }
        #ifndef ONLINE_JUDGE
            std::cout << "p: " << i << " " << k << std::endl;
        #endif
        res = std::min(res, fleurs::Segment<T>(p[i], p[(i + 1) % n]).distance(p[k]));
        #ifndef ONLINE_JUDGE
            std::cout << "r: " << res << std::endl;
        #endif
    }
    return res;
}
}

template <typename T, typename F> 
T operator|(const fleurs::Polygon<T>& a, const F b) {
    T res = b(a);
    return res;
}

void solve() {
    int n = 0;
    fleurs::Polygon<fleurs::Real> p;
    std::cin >> p;
    fleurs::Polygon<fleurs::Real> ch = p.convexHull();
    std::function<fleurs::Real (fleurs::Polygon<fleurs::Real>)> f = fleurs::rotcaliper<fleurs::Real>;
    std::cout << std::fixed << std::setprecision(2) << (ch | f) << std::endl;
}

auto main() -> signed {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t = 1;
    std::cin >> t;
    for(int __case = 1; __case <= t; __case++) {
        solve();
    }
    return 0;
}