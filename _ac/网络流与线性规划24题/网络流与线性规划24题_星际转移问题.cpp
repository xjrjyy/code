/* 网络流与线性规划24题_星际转移问题.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : s)
#define all(s) (s).begin(), (s).end()
#define dbg(x) (cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>; using namespace std;

struct DSU {
    int n; vec<int> fa, sz;
    DSU(int n_) : n(n_), fa(n), sz(n, 1) { iota(all(fa), 0); }
    int fd(int x) { return x == fa[x] ? x : fa[x] = fd(fa[x]); }
    void mg(int u, int v) {
        if ((u = fd(u)) == (v = fd(v))) return;
        if (sz[u] < sz[v]) swap(u, v);
        fa[v] = u, sz[u] += sz[v];
    }
};
template <typename T> class NetFlow {
public:
    struct Edge { int u, v; T w, f; };
    NetFlow(int n_) : n(n_), G(n), d(n), h(n) {}
    void adde(int u, int v, T w) {
        auto add = [&](int u, int v, T w, T f) {
            G[u].push_back(int(E.size())), E.push_back({u, v, w, f});
        };
        add(u, v, w, 0), add(v, u, w, w);
    }
    T max_flow(int s_, int t_, T mf) {
        T f = T(); s = s_, t = t_;
        // r0p (i, int(E.size())) E[i].f = (i & 1 ? E[i].w : T());
        int tt = 0;
        while (bfs()) fill(all(h), 0), f += dfs(s, mf), ++tt;
        if (tt) cerr << tt << ' ';
        return f;
    }
    vec<Edge> &edges() { return E; }
    const vec<Edge> &edges() const { return E; }
private:
    bool bfs() {
        static queue<int> Q;
        fill(all(d), -1), d[s] = 0, Q.push(s);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            each (i, G[u]) {
                int v = E[i].v; T w = E[i].w - E[i].f;
                if (w && !~d[v]) d[v] = d[u] + 1, Q.push(v);
            }
        }
        return ~d[t];
    }
    T dfs(int u, T mf) {
        T f = T(); if (u == t) return mf;
        for (int &_ = h[u]; f < mf && _ < int(G[u].size()); ++_) {
            int i = G[u][_], v = E[i].v; T w = E[i].w - E[i].f;
            if (w && d[v] == d[u] + 1) {
                T t = dfs(v, min(w, mf - f));
                E[i].f += t, E[i ^ 1].f -= t, f += t;
            }
        }
        return f;
    }
    int n, s, t; vec<Edge> E; vec<vec<int>> G;
    vec<int> d, h;
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, k; cin >> n >> m >> k, n += 2;
    const int r = n, T = (n - 1 + k) * r;
    const int inf = ~0u >> 2;
    vec<int> a(m); vec<vec<int>> b(m); DSU dsu(n);
    r0p (i, m) {
        cin >> a[i];
        int t; cin >> t, b[i].resize(t);
        each (x, b[i]) cin >> x, x = (~x ? x : n - 1);
        rep (j, 1, t - 1) dsu.mg(b[i][j], b[i][j - 1]);
    }
    if (dsu.fd(0) != dsu.fd(n - 1)) return cout << 0 << '\n', 0;
    NetFlow<int> nf(n * T + 2); int s = n * T, t = s + 1;
    auto Id = [&](int t, int x) { return x + t * n; };
    int A = 0; nf.adde(s, Id(0, 0), inf), nf.adde(Id(0, n - 1), t, inf);
    while (k > 0) {
        r0p (i, n) nf.adde(Id(A, i), Id(A + 1, i), inf);
        r0p (i, m) {
            int u = b[i][A % b[i].size()], v = b[i][(A + 1) % b[i].size()];
            nf.adde(Id(A, u), Id(A + 1, v), a[i]);
        }
        nf.adde(Id(A + 1, n - 1), t, inf);
        k -= nf.max_flow(s, t, inf);
        ++A;
    }
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
