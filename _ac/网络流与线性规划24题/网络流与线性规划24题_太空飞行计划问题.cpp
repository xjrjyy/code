/* 网络流与线性规划24题_太空飞行计划问题.cpp */
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
        r0p (i, int(E.size())) E[i].f = (i & 1 ? E[i].w : T());
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
    const int inf = ~0u >> 2;
    int n, m, k = 0; cin >> n >> m;
    NetFlow<int> nf(n + m + 2); int s = n + m, t = s + 1;
    r0p (i, n) {
        int x; cin >> x, k += x;
        nf.adde(s, i, x);
        while (true) {
            int x; char c; cin >> x, c = cin.get(), --x;
            nf.adde(i, x + n, inf);
            if (c != ' ') break;
        }
    }
    r0p (i, m) { int x; cin >> x; nf.adde(i + n, t, x); }
    int A = k - nf.max_flow(s, t, inf);
    vec<vec<int>> G(n + m + 2);
    each (e, nf.edges()) if (e.f < e.w) G[e.u].push_back(e.v);
    vec<int> vs(n + m);
    function<void(int)> dfs = [&](int u) {
        if (u < n + m) vs[u] = 1;
        each (v, G[u]) if (!vs[v]) dfs(v);
    };
    dfs(s);
    r0p (i, n) if (vs[i]) cout << i + 1 << ' ';
    cout << '\n';
    r0p (i, m) if (vs[i + n]) cout << i + 1 << ' ';
    cout << '\n';
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
