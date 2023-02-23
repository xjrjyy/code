/* apio2020_b_swap.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = (l), rep##i = (r); i <= rep##i; ++i)
#define per(i, r, l) for (int i = (r), per##i = (l); i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : (s))
#define all(s) (s).begin(), (s).end()
#define dbg(x) (cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>; using namespace std;

#include "swap.h"

struct DSU {
    vec<int> fa;
    DSU(int n) : fa(n) { iota(all(fa), 0); }
    int fd(int x) { return x == fa[x] ? x : fa[x] = fd(fa[x]); }
    bool mg(int u, int v) {
        if ((u = fd(u)) == (v = fd(v))) return false;
        return fa[v] = u, true;
    }
};

struct edge { int u, v, w; };
bool operator<(const edge &x, const edge &y) { return x.w < y.w; }
struct chain {
    int s, t;
    chain(int u = -1) : s(u), t(u) {}
    chain(int s_, int t_) : s(s_), t(t_) {}
    bool operator()() const { return ~s && ~t; }
    int gt(int u) const { return u == s ? t : u == t ? s : -1; }
    friend chain operator+(const chain &x, const chain &y) {
        if (~y.gt(x.s)) return chain(x.t, y.gt(x.s));
        if (~y.gt(x.t)) return chain(x.s, y.gt(x.t));
        return chain();
    }
};

const int maxk = 2e5 + 5;
const int maxq = 20;
const int inf = ~0u >> 1;

int k, q, a[maxk], dp[maxk], fa[maxq][maxk];

void init(int n, int m, vec<int> U, vec<int> V, vec<int> W) {
    vec<edge> E;
    r0p (i, m) E.push_back({U[i], V[i], W[i]});
    sort(all(E));
    k = n;
    vec<chain> b(2 * n); r0p (i, n) b[i] = chain(i);
    vec<int> vs(2 * n); DSU c(2 * n), d(2 * n);
    auto upd = [&](int u, int v, int w) {
        fa[0][u] = fa[0][v] = k;
        d.mg(k, u), d.mg(k, v), a[k] = w, ++k;
    };
    each (e, E) {
        int u = e.u, v = e.v, w = e.w, x = c.fd(u), y = c.fd(v);
        if (x != y && !vs[x] && !vs[y]) {
            chain p = b[x], q = b[y], r = p + chain(u, v) + q;
            if (r()) {
                c.mg(k, x), c.mg(k, y), b[k] = r, upd(x, y, inf);
                continue;
            }
        }
        vs[x] = vs[y] = 1;
        if ((x = d.fd(x)) == (y = d.fd(y))) a[x] = min(a[x], w);
        else upd(x, y, w);
    }
    int s = -1; r0p (i, k) if (c.fd(i) == i) { s = i; break; }
    r0p (i, k) if (c.fd(i) == i && d.fd(i) != d.fd(s)) upd(d.fd(i), d.fd(s), inf);
    q = ceil(log2(k)) + 1, fa[0][k - 1] = k - 1;
    p0r (u, k) dp[u] = dp[fa[0][u]] + 1, a[u] = min(a[u], a[fa[0][u]]);
    replace(a, a + k, inf, -1);
    rep (i, 1, q) r0p (u, k) fa[i][u] = fa[i - 1][fa[i - 1][u]];
}

int LCA(int u, int v) {
    if (dp[u] > dp[v]) swap(u, v);
    per (i, q, 0) if (dp[u] <= dp[fa[i][v]]) v = fa[i][v];
    per (i, q, 0) if (fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
    return u == v ? u : fa[0][u];
}

int getMinimumFuelCapacity(int u, int v) {
    return a[LCA(u, v)];
}
