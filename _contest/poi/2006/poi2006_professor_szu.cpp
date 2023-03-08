/* poi2006_professor_szu.cpp */
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

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    const int inf = 36501;
    int n, m, s; std::cin >> n >> m, s = n++;
    vec<vec<int>> G(n); vec<int> a(n);
    r0p (_, m) {
        int u, v; std::cin >> u >> v, --u, --v;
        if (u != v) G[u].push_back(v);
        else a[u] = 1;
    }
    vec<int> dfn(n, -1), low(n), S, vs(n), scn(n, -1), b; int dtt = 0;
    std::function<void(int)> dfs = [&](int u) {
        dfn[u] = low[u] = dtt++, S.push_back(u), vs[u] = 1;
        each (v, G[u]) {
            if (!~dfn[v]) dfs(v), low[u] = std::min(low[u], low[v]);
            else if (vs[v]) low[u] = std::min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u]) {
            int v, t = int(b.size()), sz = 0; b.push_back(0);
            do vs[v = S.back()] = 0, scn[v] = t, ++sz, b[t] |= a[v];
            while (S.pop_back(), v != u);
            b[t] |= (sz > 1);
        }
    };
    r0p (u, n) if (!~dfn[u]) dfs(u);
    int N = int(b.size()); vec<vec<int>> g(N); vec<int> d(N);
    r0p (u, n) each (v, G[u]) if (scn[u] != scn[v])
        g[scn[v]].push_back(scn[u]), ++d[scn[u]];
    std::queue<int> Q; r0p (u, N) if (!d[u]) Q.push(u);
    vec<int> f(N);
    auto upd = [&](int u, int w) {
        if (!w) return;
        if (!f[u] && b[u]) f[u] = inf;
        f[u] = std::min(f[u] + w, inf);
    };
    upd(scn[s], 1);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        each (v, g[u]) if (upd(v, f[u]), !--d[v]) Q.push(v);
    }
    vec<int> A; int B = 0; r0p (u, n - 1) B = std::max(B, f[scn[u]]);
    r0p (u, n - 1) if (f[scn[u]] == B) A.push_back(u);
    if (B == inf) std::cout << "zawsze\n";
    else std::cout << B << '\n';
    std::cout << A.size() << '\n';
    each (x, A) std::cout << x + 1 << ' ';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
