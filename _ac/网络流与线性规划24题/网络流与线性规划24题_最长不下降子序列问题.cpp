/* 网络流与线性规划24题_最长不下降子序列问题.cpp */
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
        while (bfs()) fill(all(h), 0), f += dfs(s, mf);
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
    int n; cin >> n;
    vec<int> a(n); each (x, a) cin >> x;
    vec<int> f(n, 1);
    r0p (i, n) r0p (j, i) if (a[j] <= a[i]) f[i] = max(f[i], f[j] + 1);
    int A = *max_element(all(f));
    auto solve = [&](int k) {
        if (A == 1) return n;
        NetFlow<int> nf(2 * n + 2); int s = 2 * n, t = s + 1;
        r0p (i, n) {
            nf.adde(i, i + n, 1 + (i == 0 || i == n - 1) * k);
            if (f[i] == 1) nf.adde(s, i, n);
            if (f[i] == A) nf.adde(i + n, t, n);
            r0p (j, i) if (a[j] <= a[i] && f[i] == f[j] + 1)
                nf.adde(j + n, i, 1);
        }
        return nf.max_flow(s, t, n);
    };
    cout << A << '\n' << solve(0) << '\n' << solve(n) << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
