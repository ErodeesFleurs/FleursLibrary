#ifndef FLEURS_LAZYSEGTREE_HPP
#define  FLEURS_LAZYSEGTREE_HPP 1

#include <vector>
#include <cassert>

namespace fleurs {

template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
struct lazysegtree {
    int n, size ,log;
    std::vector<S> d;
    std::vector<F> lz;

    lazysegtree() : lazysegtree(0) {}
    explicit lazysegtree(int n_) : lazysegtree(std::vector<S>(n_, e())) {}
    explicit lazysegtree(const std::vector<S>& v) : n(int(v.size())) {
        unsigned int x = 1;
        while(x < (unsigned int)(n)) x <<= 1;
        size = x;
        log = 0;
        for(int i = 0; i != 64; i++) {
            if(x >> i & 1) log = i;
        }
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }
    //Assigns x to a[p].
    void set(int p, S x) {
        assert(0 <= p && p < n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    //Returns a[p].
    S get(int p) {
        assert(0 <= p && p < n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
    //Returns op(a[l], ..., a[r - 1]).
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return e();
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
    //Returns op(a[0], ..., a[n - 1]).
    S all_prod() {
        return d[1];
    }
    //Assigns f to a[p].
    void apply(int p, F f) {
        assert(0 <= p && p < n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    //Assigns f to a[l], ..., a[r - 1].
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
    //Binary search in range [l, n) .
    //Return max r that satisfies f(op(a[l], ..., a[r - 1])) = true, or n if it does not exist.
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= n);
        assert(g(e()));
        if (l == n) return n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = 2 * l;
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }
    //Binary search in range [0, r) .
    //Return min l that satisfies f(op(a[l], ..., a[r - 1])) = true, or -1 if it does not exist.
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = 2 * r + 1;
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
    void update(int k) {
        d[k] = op(d[2 * k], d[2 * k + 1]);
    }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};


} // namespace fleurs

#endif // FLEURS_LAZYSEGTREE_HPP