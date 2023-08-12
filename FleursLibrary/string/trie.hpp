#include <array>
#ifndef FLEURS_TRIE_HPP
#define FLEURS_TRIE_HPP 1

#include <string>
#include <vector>

namespace fleurs {

template <class T, int mx = 30> struct binary_trie {
  int n = 0;
  std::vector<std::array<int, 3>> next; // leftchild, rightchild, count
  binary_trie() { next.push_back({0, 0, 0}); }
  binary_trie(const std::vector<T> &a) {
    next.push_back({0, 0, 0});
    for (auto x : a)
      insert(x);
  }
  void insert(T x) {
    ++n;
    for (int bit = mx - 1, u = 0; bit >= 0; --bit) {
      if (!next[u][x >> bit & 1]) {
        next[u][x >> bit & 1] = (int)next.size();
        next.push_back({0, 0, 0});
      }
      u = next[u][x >> bit & 1];
      ++next[u][2];
    }
  }
  void erase(T x) {
    --n;
    for (int bit = mx - 1, u = 0; bit >= 0; --bit) {
      assert(next[u][x >> bit & 1]);
      u = next[u][x >> bit & 1];
      assert(next[u][2]);
      --next[u][2];
    }
  }
  T max_xor(T x) {
    if (!n) {
      return std::numeric_limits<T>::min();
    }
    T res = 0;
    for (int bit = mx - 1, u = 0; bit >= 0; --bit) {
      if (!next[u][~x >> bit & 1] || !next[next[u][~x >> bit & 1]][2])
        u = next[u][x >> bit & 1];
      else {
        res |= T(1) << bit;
        u = next[u][~x >> bit & 1];
      }
    }
    return res;
  }
  T min_xor(T x) {
    if (!n) {
      return std::numeric_limits<T>::max();
    }
    T res = 0;
    for (int bit = mx - 1, u = 0; bit >= 0; --bit) {
      if (!next[u][x >> bit & 1] || !next[next[u][x >> bit & 1]][2]) {
        res |= T(1) << bit;
        u = next[u][~x >> bit & 1];
      } else
        u = next[u][x >> bit & 1];
    }
    return res;
  }
};

// Adjacency_Type compressed is std::vector<int> or std::array<int, 256>
template <class Char_Type, class Adjacency_Type> struct trie {
  int n = 1; // # of active nodes(cnt != 0)
  std::vector<Adjacency_Type> next{{}};
  std::vector<Adjacency_Type> exist{{}};
  std::vector<int> cnt{1};
  trie() {}
  trie(const std::vector<Adjacency_Type> &next, const std::vector<int> &cnt)
      : n((int)next.size()), next(next), cnt(cnt) {}
  int extend() {
    next.emplace_back();
    exist.emplace_back();
    cnt.push_back(0);
    return (int)next.size() - 1;
  }
  void insert(const std::vector<Char_Type> &a, int u = 0) {
    if (!cnt[u]++)
      ++n;
    for (auto c : a) {
      if (!next[u][c])
        next[u][c] = extend();
      u = next[u][c];
      if (!cnt[u]++)
        ++n;
    }
    exist[u][a.back()] = 1;
  }
  void erase(const std::vector<Char_Type> &a, int u = 0) {
    assert(cnt[u]);
    if (!--cnt[u])
      --n;
    for (auto c : a) {
      u = next[u][c];
      assert(u && cnt[u]);
      if (!--cnt[u])
        --n;
    }
    exist[u][a.back()] = 0;
  }
  bool find(const std::vector<Char_Type> &a, int u = 0) {
    for (auto c : a) {
      if (!next[u][c])
        return false;
      u = next[u][c];
    }
    return true;
  }
  int size() const { // # of states
    return (int)cnt.size();
  }
};

} // namespace fleurs

#endif // FLEURS_TRIE_HPP
