/* cf_573_c.cpp */
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
    int n; std::cin >> n; if (n == 1) return std::cout << "Yes\n", 0;
    vec<vec<int>> G(n); vec<int> d(n);
    r0p (_, n - 1) {
        int u, v; std::cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u), ++d[u], ++d[v];
    }
    if (std::all_of(all(d), [](int x) { return x <= 2; })) return std::cout << "Yes\n", 0;
    vec<int> c(n);
    std::function<int(int, int)> fd = [&](int u, int fa) {
        each (v, G[u]) if (v != fa) {
            if (d[v] >= 3 && ~fa) return u;
            int w = fd(v, u); c[u] += bool(c[v]); if (~w) return w;
        }
        if (c[u] >= 2) return u;
        return c[u] += (d[u] >= 3), -1;
    };
    int rt = std::find_if(all(d), [](int x) { return x >= 4; }) - d.begin();
    if (rt == n) rt = fd(std::find_if(all(d), [](int x) { return x >= 3; }) - d.begin(), -1);
    if (!~rt) return std::cout << "Yes\n", 0;
    vec<int> a(n), b(n);
    std::function<void(int, int)> dfs = [&](int u, int fa) {
        if (d[u] >= 4) a[u] = 1;
        if (d[u] == 3) a[fa] = 1;
        each (v, G[u]) if (v != fa) dfs(v, u);
    };
    std::function<void(int, int)> dfs2 = [&](int u, int fa) {
        each (v, G[u]) if (v != fa) dfs2(v, u), a[u] += a[v], b[u] += bool(a[v]);
    };
    dfs(rt, rt), dfs2(rt, rt);
    int A = 1; r0p (u, n) A &= (b[u] <= 1 + (u == rt));
    std::cout << (A ? "Yes" : "No") << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
