/* ioi2019_1b_split.cpp */
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

#include "split.h"

vector<int> find_split(int n, int X, int Y, int Z, vector<int> p, vector<int> q) {
    int P[4] = {0, 1, 2, 3};
    if (X > Y) swap(X, Y), swap(P[1], P[2]);
    if (X > Z) swap(X, Z), swap(P[1], P[3]);
    if (Y > Z) swap(Y, Z), swap(P[2], P[3]);
    int m = int(p.size()); vec<vec<int>> G(n), g(n);

    r0p (i, m) G[p[i]].push_back(q[i]), G[q[i]].push_back(p[i]);
    vec<int> A(n);
    function<void(int, int &, int)> draw = [&](int u, int &c, int t) {
        if (!c) return;
        A[u] = t, --c;
        each (v, g[u]) if (!A[v]) draw(v, c, t);
    };
    function<void(int, int &, int)> draw2 = [&](int u, int &c, int t) {
        if (!c) return;
        A[u] = t, --c;
        each (v, G[u]) if (!A[v]) draw2(v, c, t);
    };
    auto outp = [&](int u, int v, int p, int q) {
        if (p >= X && q >= Y) draw(u, X, P[1]), draw2(v, Y, P[2]);
        else draw(u, Y, P[2]), draw2(v, X, P[1]);
    };

    vec<int> vs(n), sz(n, 1), fa(n, -1); vec<pair<int, int>> O; int s = -1;
    function<void(int)> dfs = [&](int u) {
        vs[u] = 1;
        each (v, G[u]) {
            if (!vs[v]) fa[v] = u, dfs(v), sz[u] += sz[v], g[u].push_back(v);
            else if (sz[u] > sz[v]) O.push_back({u, v});
        }
        if (sz[u] >= X && !~s) s = u;
    };
    dfs(0); int S = sz[s];
    if (S <= n - X) {
        outp(s, 0, S, n - S), replace(all(A), 0, P[3]);
        return A;
    }
    vec<int> fx(n, -1);
    function<void(int)> dfs2 = [&](int u) {
        each (v, g[u]) fx[v] = fx[u], dfs2(v);
    };
    vec<int> Vs(n);
    each (v, g[s]) Vs[v] = 1, fx[v] = v, dfs2(v);
    each (p, O) {
        int u = p.first, v = p.second;
        if (u == s || v == s || !~(u = fx[u]) == !~(v = fx[v])) continue;
        if (!~v) swap(u, v);
        S -= sz[v], sz[v] = 0;
        if (S <= n - X) break;
    }
    if (S > n - X) return vec<int>(n);
    g[s].erase(partition(all(g[s]), [&](int u) { return sz[u] > 0; }), g[s].end());
    outp(s, fa[s], S, n - S), replace(all(A), 0, P[3]);
    return A;
}
