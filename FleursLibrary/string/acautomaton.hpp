#ifndef FLEURS_ACAUTOMATON_HPP
#define FLEURS_ACAUTOMATON_HPP 1

#include <array>
#include <cassert>
#include <queue>
#include <string.h>
#include <string>
#include <vector>

namespace fleurs {

struct AhoCorasick {
  // change this!
  enum { alpha = 26, first = 'a' };
  struct Node {
    // (nmatches is optional)
    // back is fail
    int back, next[alpha], start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  std::vector<Node> N;
  std::vector<int> backp;
  std::vector<std::vector<int>> mp;
  std::vector<int> ans;

  void insert(std::string &s, int j) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int &m = N[n].next[c - first];
      if (m == -1) {
        n = m = N.size();
        N.emplace_back(-1);
      } else
        n = m;
    }
    if (N[n].end == -1)
      N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    // N[n].nmatches++;
  }
  AhoCorasick(std::vector<std::string> &pat) : N(1, -1) {
    for (int i = 0; i < pat.size(); i++)
      insert(pat[i], i);
    N[0].back = N.size();
    N.emplace_back(0);
    std::queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      for (int i = 0; i < alpha; i++) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1)
          ed = y;
        else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
          // N[ed].nmatches += N[y].nmatches;
          q.push(ed);
        }
      }
    }
  }
  std::vector<int> find(std::string word) {
    int n = 0;
    std::vector<int> res; // ll count = 0;
    for (char c : word) {
      n = N[n].next[c - first];
      res.push_back(N[n].end);
      N[n].nmatches++;
      // count += N[n].nmatches;
    }
    return res;
  }
  std::vector<std::vector<int>> findAll(std::vector<std::string> &pat,
                                        std::string word) {
    std::vector<int> r = find(word);
    std::vector<std::vector<int>> res(word.size());
    for (int i = 0; i < word.size(); ++i) {
      int ind = r[i];
      while (ind != -1) {
        res[i - pat[ind].size() + 1].push_back(ind);
        ind = backp[ind];
      }
    }
    return res;
  }

  void dfs(int u) {
    for (auto v : mp[u]) {
      if (v == u)
        continue;
      dfs(v);
      N[u].nmatches += N[v].nmatches;
    }
    if (N[u].end != -1 && N[u].start != -1) {
      ans[N[u].end] += N[u].nmatches;
    }
  }

  void failTree() {
    ans.resize(backp.size());
    mp.resize(N.size());
    for (int i = 1; i < N.size() - 1; ++i) {
      mp[N[i].back].push_back(i);
    }
    dfs(0);
    return;
  }
};

} // namespace fleurs

#endif // FLEURS_ACAUTOMATON_HPP
