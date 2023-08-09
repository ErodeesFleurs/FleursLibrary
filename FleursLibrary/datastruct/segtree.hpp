#ifndef FLEURS_SEGTREE_HPP
#define FLEURS_SEGTREE_HPP 1

#include <vector>
#include <cassert>

namespace fleurs {

template <class S, auto op, auto e>
struct segtree {
    int n, size, log;
    std::vector<S> d;

    segtree() : segtree(0) {}
    explicit segtree(int _n) : segtree(std::vector<S>(_n, e())) {}
    explicit segtree(const std::vector<S>& v) : n(int(v.size())) {
        unsigned int x = 1;
        while(x < (unsigned int)(n)) x <<= 1;
        size = x;
        log = 0;
        for(int i = 0; i != 64; i++) {
            if(x >> i & 1) log = i;
        }
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }
    //Assigns x to a[p].
    void set(int p, S x) {
        assert(0 <= p && p < n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    //Return a[p].
    S get(int p) const {
        assert(0 <= p && p < n);
        return d[p + size];
    }
    //Return op(a[l], ..., a[r - 1]).
    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        S sml = e(), smr = e();
        l += size;
        r += size;
        while(l < r) {
            if(l & 1) sml = op(sml, d[l++]);
            if(r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
    //Return op(a[0], ..., a[n - 1]).
    S all_prod() const {
        return d[1];
    }
    //Binary search in range [l, n) .
    //Return max r that satisfies f(op(a[l], ..., a[r - 1])) = true, or n if it does not exist.
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= n);
        assert(f(e()));
        if(l == n) return n;
        l += size;
        S sm = e();
        do {
            while(~l & 1) l >>= 1;
            if(!f(op(sm, d[l]))) {
                while(l < size) {
                    l = 2 * l;
                    if(f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while((l & -l) != l);
        return n;
    }
    //Binary search in range [0, r) .
    //Return min l that satisfies f(op(a[l], ..., a[r - 1])) = true, or 0 if it does not exist.
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= n);
        assert(f(e()));
        if(r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while(r > 1 && r & 1) r >>= 1;
            if(!f(op(d[r], sm))) {
                while(r < size) {
                    r = 2 * r + 1;
                    if(f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while((r & -r) != r);
        return 0;
    }
    void update(int k) {
        d[k] = op(d[2 * k], d[2 * k + 1]);
    }
};

} // namespace fleurs

#endif // FLEURS_SEGTREE_HPP