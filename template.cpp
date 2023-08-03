#include <bits/stdc++.h>

#include <FleursLibrary/geometry/polygon.hpp>

using ll = long long;
using ull = unsigned long long;

bool solve() {
    int n;
    fleurs::Polygon<fleurs::Real> p;
    std::cin >> p;
    fleurs::Polygon<fleurs::Real> newP = p.convexHull();
    double ans = 0;
    for (size_t i = 0; i < newP.size(); i++){
        fleurs::Segment<fleurs::Real> s(newP[i], newP[(i + 1) % newP.size()]);
        ans += s.length();
    }
    std::cout << std::fixed << std::setprecision(2) << ans << std::endl;
    return true;
}

signed main() {
    int t = 1;
    // std::cin >> t;
    for(int i = 0; i < t; ++i) {
        #ifdef LOCAL
        std::cout << "Case #" << i + 1 << ": " << std::endl;
        #endif
        solve();
    }
    return 0;
}
