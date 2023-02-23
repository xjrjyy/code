/* at_agc034_e.cpp */
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

const int inf = ~0u >> 2;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    string s; cin >> s;
    vec<vec<int>> G(n);
    rep (i, 1, n - 1) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u);
    }
    auto solve = [&](int rt) {
        vec<int> f(n), g(n), sz(n);
        function<void(int, int)> dfs = [&](int u, int fa) {
            sz[u] = s[u] - '0'; int mx = -1;
            each (v, G[u]) if (v != fa) {
                dfs(v, u), sz[u] += sz[v], g[v] += sz[v];
                f[u] += f[v], g[u] += g[v];
                if (!~mx || g[mx] < g[v]) mx = v;
            }
            if (!~mx) return;
            if (g[u] >= 2 * g[mx]) f[u] = g[u] / 2;
            else f[u] = g[u] - g[mx] + min(f[mx], (2 * g[mx] - g[u]) / 2);
        };
        dfs(rt, -1);
        return f[rt] * 2 != g[rt] ? inf : f[rt];
    };
    int A = inf;
    r0p (u, n) A = min(A, solve(u));
    if (A == inf) A = -1;
    cout << A << "\n";
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
