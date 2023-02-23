/* 网络流与线性规划24题_魔术球问题.cpp */
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
    cin.tie(nullptr)->sync_with_stdio(false);
    const int N = 2000;
    vec<int> vs(2 * N);
    r0p (i, 2 * N) if (i * i < 2 * N) vs[i * i] = 1;
    int n, k = 0; cin >> n;
    NetFlow<int> nf(2 * N + 2); int s = 2 * N, t = s + 1;
    int m = 0; vec<vec<int>> A(n);
    vec<int> a, to;
    function<void(int, vec<int> &)> prt = [&](int u, vec<int> &A) {
        if (to[u]) prt(to[u], A);
        A.push_back(u), a[u] = 1;
    };
    while (true) {
        each (x, A) x.clear();
        a.clear(), a.resize(m + 1);
        to.clear(), to.resize(m + 1);
        each (e, nf.edges()) if (e.u < N && N <= e.v && e.v < N + N && e.f)
            to[e.u] = e.v - N;
        int tt = 0;
        per (i, m, 1) if (!a[i]) prt(i, A[tt++]);
        ++m;
        nf.adde(s, m, 1), nf.adde(m + N, t, 1);
        rep (i, 1, m - 1) if (vs[i + m]) nf.adde(m, i + N, 1);
        k += nf.max_flow(s, t, ~0u >> 2);
        if (m - k > n) break;
    }
    cout << m - 1;
    r0p (i, n) r0p (j, int(A[i].size())) cout << " \n"[!j] << A[i][j];
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
