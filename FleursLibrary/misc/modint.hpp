#ifndef FLEURS_MODINT_HPP
#define FLEURS_MODINT_HPP 1

#include <algorithm>
#include <iostream>

namespace fleurs {

template <typename T, T MOD> struct modint {
  T x;
  modint() : x(0) {}
  modint(T x) : x(x) {}
  modint &operator=(const modint &m) {
    x = m.x;
    return *this;
  }
  modint &operator+=(const modint &m) {
    if ((x += m.x) >= MOD)
      x -= MOD;
    return *this;
  }
  modint &operator-=(const modint &m) {
    if ((x += MOD - m.x) >= MOD)
      x -= MOD;
    return *this;
  }
  modint &operator*=(const modint &m) {
    x = (long long)x * m.x % MOD;
    return *this;
  }
  modint &operator/=(const modint &m) { return *this *= m.inv(); }
  modint operator+(const modint &m) const { return modint(*this) += m; }
  modint operator-(const modint &m) const { return modint(*this) -= m; }
  modint operator*(const modint &m) const { return modint(*this) *= m; }
  modint operator/(const modint &m) const { return modint(*this) /= m; }
  bool operator==(const modint &m) const { return x == m.x; }
  bool operator!=(const modint &m) const { return x != m.x; }
  bool operator<(const modint &m) const { return x < m.x; }
  bool operator>(const modint &m) const { return x > m.x; }
  bool operator<=(const modint &m) const { return x <= m.x; }
  bool operator>=(const modint &m) const { return x >= m.x; }
  modint inv() const {
    T a = x, b = MOD, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      a -= t * b;
      std::swap(a, b);
      u -= t * v;
      std::swap(u, v);
    }
    return modint(u);
  }
  modint pow(long long n) const {
    modint res(1), a(x);
    while (n > 0) {
      if (n & 1)
        res *= a;
      a *= a;
      n >>= 1;
    }
    return res;
  }
  friend std::ostream &operator<<(std::ostream &os, const modint &m) {
    return os << m.x;
  }
  friend std::istream &operator>>(std::istream &is, modint &m) {
    long long x;
    is >> x;
    m = modint(x);
    return is;
  }
};

} // namespace fleurs

#endif // FLEURS_MODINT_HPP
