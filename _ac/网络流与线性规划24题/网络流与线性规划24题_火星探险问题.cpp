/* 网络流与线性规划24题_火星探险问题.cpp */
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

template <typename T, typename U> class CostNetFlow {
public:
    struct Edge { int u, v; T w, f; U c; };
    struct Flow {
        T f; U c;
        Flow operator+(const Flow &y) const { return {f + y.f, c + y.c}; }
        Flow &operator+=(const Flow &y) { return f += y.f, c += y.c, *this; }
    };
    CostNetFlow(int n_) : n(n_), G(n), d(n), h(n), vs(n) {}
    void adde(int u, int v, T w, U c) {
        auto add = [&](int u, int v, T w, T f, U c) {
            G[u].push_back(int(E.size())), E.push_back({u, v, w, f, c});
        };
        add(u, v, w, T(), c), add(v, u, w, w, -c);
    }
    Flow max_flow(int s_, int t_, T mf) {
        Flow f = {T(), U()}; s = s_, t = t_;
        r0p (i, int(E.size())) E[i].f = (i & 1 ? E[i].w : T());
        while (spfa()) fill(all(h), 0), f += dfs(s, mf);
        return f;
    }
    vec<Edge> &edges() { return E; }
    const vec<Edge> &edges() const { return E; }
private:
    bool spfa() {
        static queue<int> Q; static vec<bool> V;
        V.clear(), V.resize(n);
        V[s] = true, fill(all(vs), false), d[s] = U(), Q.push(s);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop(), vs[u] = false;
            each (i, G[u]) {
                int v = E[i].v; T w = E[i].w - E[i].f; U c = E[i].c;
                if (w && (!V[v] || d[v] > d[u] + c)) {
                    V[v] = true, d[v] = d[u] + c;
                    if (!vs[v]) Q.push(v), vs[v] = true;
                }
            }
        }
        return V[t];
    }
    Flow dfs(int u, T mf) {
        Flow f = {T(), U()}; if (u == t) return {mf, U()};
        vs[u] = true;
        for (int &_ = h[u]; f.f < mf && _ < int(G[u].size()); ++_) {
            int i = G[u][_], v = E[i].v; T w = E[i].w - E[i].f; U c = E[i].c;
            if (!vs[v] && w && d[v] == d[u] + c) {
                Flow t = dfs(v, min(w, mf - f.f));
                E[i].f += t.f, E[i ^ 1].f -= t.f, f += t, f.c += t.f * c;
            }
        }
        return vs[u] = false, f;
    }
    int n, s, t; vec<Edge> E; vec<vec<int>> G;
    vec<U> d; vec<int> h; vec<bool> vs;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    const vec<int> Dx = {1, 0};
    const vec<int> Dy = {0, 1};
    int n, m, k; cin >> k >> m >> n;
    vec<vec<int>> a(n, vec<int>(m)); each (x, a) each (y, x) cin >> y;
    CostNetFlow<int, int> nf(2 * n * m + 2); int s = 2 * n * m, t = s + 1;
    auto in = [&](int x) { return 0 <= x && x < n * m; };
    auto id = [&](int t, int x, int y) { return t * n * m + x * m + y; };
    nf.adde(s, id(0, 0, 0), k, 0);
    nf.adde(id(1, n - 1, m - 1), t, k, 0);
    r0p (i, n) r0p (j, m) if (a[i][j] != 1) {
        if (a[i][j] == 2) nf.adde(id(0, i, j), id(1, i, j), 1, -1);
        nf.adde(id(0, i, j), id(1, i, j), k, 0);
        if (i + 1 < n) nf.adde(id(1, i, j), id(0, i + 1, j), k, 0);
        if (j + 1 < m) nf.adde(id(1, i, j), id(0, i, j + 1), k, 0);
    }
    int A = nf.max_flow(s, t, k).f;
    vec<vec<int>> G(n * m); vec<int> h(n * m);
    each (e, nf.edges()) if (in(e.u - n * m) && in(e.v) && e.u - n * m < e.v)
        r0p (_, e.f) G[e.u - n * m].push_back(e.v);
    function<void(int)> prt = [&](int u) {
        int &i = h[u]; if (i == int(G[u].size())) return;
        int v = G[u][i++]; assert(v - u == 1 || v - u == m);
        cout << A + 1 << ' ' << (v - u == 1) << '\n';
        prt(v);
    };
    while (A--) prt(0);
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
