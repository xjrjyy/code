/* poi2008_blockade.cpp */
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
    int n, m; std::cin >> n >> m;
    vec<vec<int>> G(n);
    r0p (_, m) {
        int u, v; std::cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u);
    }
    vec<int> dfn(n, -1), low(n), sz(n, 1); int dtt = 0;
    auto C2 = [](int x) { return 1ll * x * (x - 1) / 2; };
    vec<ll> A(n);
    std::function<void(int, int)> dfs = [&](int u, int fa) {
        dfn[u] = low[u] = dtt++; int s = 0;
        each (v, G[u]) if (v != fa) {
            if (!~dfn[v]) {
                dfs(v, u), sz[u] += sz[v], low[u] = std::min(low[u], low[v]);
                if (dfn[u] <= low[v]) A[u] -= C2(sz[v]), s += sz[v];
            } else low[u] = std::min(low[u], dfn[v]);
        }
        if (s) A[u] += C2(n) - C2(n - s - 1);
        else A[u] = n - 1;
    };
    dfs(0, -1);
    each (x, A) std::cout << 2 * x << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
