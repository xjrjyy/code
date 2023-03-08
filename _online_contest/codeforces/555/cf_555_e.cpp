/* cf_555_e.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = (l), rep##i = (r); i <= rep##i; ++i)
#define per(i, r, l) for (int i = (r), per##i = (l); i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : (s))
#define all(s) (s).begin(), (s).end()
#define dbg(x) (std::cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << std::endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>;

struct LCA {
    int n, m; vec<vec<int>> G, fa; vec<int> dp;
    LCA(int n_) : n(n_), m(std::log2(n) + 1), G(n), fa(m, vec<int>(n)), dp(n) {}
    void add(int u, int v) { G[u].push_back(v); }
    void init(const vec<int> &rt) {
        std::function<void(int)> dfs = [&](int u) {
            each (v, G[u]) if (v != fa[0][u]) fa[0][v] = u, dp[v] = dp[u] + 1, dfs(v);
        };
        each (s, rt) fa[0][s] = s, dfs(s);
        rep (i, 1, m - 1) r0p (u, n) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    }
    int operator()(int u, int v) {
        if (dp[u] > dp[v]) std::swap(u, v);
        p0r (i, m) if (dp[u] <= dp[fa[i][v]]) v = fa[i][v];
        p0r (i, m) if (fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
        return u == v ? u : fa[0][u];
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, q; std::cin >> n >> m >> q;
    vec<vec<std::pair<int, int>>> G(n);
    r0p (i, m) {
        int u, v; std::cin >> u >> v, --u, --v;
        G[u].push_back({v, i}), G[v].push_back({u, i});
    }
    vec<int> tim(n), dfn(n, -1), low(n), scn(n), S; int dt = 0, N = 0, tt = 0;
    std::function<void(int, int)> dfs = [&](int u, int fr) {
        tim[u] = tt, dfn[u] = low[u] = dt++, S.push_back(u);
        each (p, G[u]) {
            int v = p.first, w = p.second;
            if (!~dfn[v]) dfs(v, w), low[u] = std::min(low[u], low[v]);
            else if (w != fr) low[u] = std::min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u]) for (int v = -1, t = N++; v != u; scn[v = S.back()] = t, S.pop_back());
    };
    vec<int> rt;
    r0p (u, n) if (!~dfn[u]) dfs(u, -1), rt.push_back(scn[u]), ++tt;
    LCA lca(N);
    r0p (u, n) each (p, G[u]) if (scn[u] != scn[p.first]) lca.add(scn[u], scn[p.first]);
    lca.init(rt); vec<int> a(N), b(N);
    r0p (_, q) {
        int u, v; std::cin >> u >> v, --u, --v;
        if (tim[u] != tim[v]) return std::cout << "No\n", 0;
        if ((u = scn[u]) != (v = scn[v])) {
            int l = lca(u, v);
            ++a[u], --a[l], ++b[v], --b[l];
        }
    }
    std::function<void(int, int)> dfs2 = [&](int u, int fa) {
        each (v, lca.G[u]) if (v != fa) dfs2(v, u), a[u] += a[v], b[u] += b[v];
        if (a[u] && b[u]) std::cout << "No\n", exit(0);
    };
    each (s, rt) dfs2(s, -1);
    std::cout << "Yes\n";
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
