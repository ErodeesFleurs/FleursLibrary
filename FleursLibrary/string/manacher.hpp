#ifndef FLEURS_MANACHER_HPP
#define FLEURS_MANACHER_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

namespace fleurs {

template <typename S> std::vector<int> manacher(S s, bool calc_even = true) {
  if (calc_even) {
    int n = (int)s.size();
    assert(n > 0);
    s.resize(2 * n - 1);
    for (int i = n - 1; i >= 0; i--) {
      s[2 * i] = s[i];
    }
    auto d = *std::min_element(begin(s), end(s));
    for (int i = 0; i < n - 1; i++) {
      s[2 * i + 1] = d;
    }
  }
  int n = (int)s.size();
  std::vector<int> rad(n);
  {
    int i = 0, j = 0;
    while (i < n) {
      while (i - j >= 0 && i + j < n && s[i - j] == s[i + j])
        ++j;
      rad[i] = j;
      int k = 1;
      while (i - k >= 0 && i + k < n && k + rad[i - k] < j) {
        rad[i + k] = rad[i - k];
        ++k;
      }
      i += k, j -= k;
    }
  }
  if (calc_even) {
    for (int i = 0; i < n; i++) {
      if (((i ^ rad[i]) & 1) == 0)
        rad[i]--;
    }
  } else {
    for (auto &&x : rad)
      x = 2 * x - 1;
  }
  return rad;
}

} // namespace fleurs

#endif // FLEURS_MANACHER_HPP
