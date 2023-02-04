/* 网络流与线性规划24题_深海机器人问题.cpp */
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
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    const int inf = ~0u >> 2;
    int p, q, n, m; cin >> p >> q >> n >> m;
    CostNetFlow<int, int> nf(2 * (n + 1) * (m + 1) + 2); int s = 2 * (n + 1) * (m + 1), t = s + 1;
    auto id = [&](int x, int y) { return x * (m + 1) + y; };
    r0p (i, n + 1) r0p (j, m) {
        int x; cin >> x;
        nf.adde(id(i, j), id(i, j + 1), 1, -x);
        nf.adde(id(i, j), id(i, j + 1), inf, 0);
    }
    r0p (j, m + 1) r0p (i, n) {
        int x; cin >> x;
        nf.adde(id(i, j), id(i + 1, j), 1, -x);
        nf.adde(id(i, j), id(i + 1, j), inf, 0);
    }
    r0p (_, p) {
        int k, x, y; cin >> k >> x >> y;
        nf.adde(s, id(x, y), k, 0);
    }
    r0p (_, q) {
        int k, x, y; cin >> k >> x >> y;
        nf.adde(id(x, y), t, k, 0);
    }
    cout << -nf.max_flow(s, t, inf).c << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
