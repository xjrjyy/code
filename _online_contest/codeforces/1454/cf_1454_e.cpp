/* cf_1454_e.cpp */
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
    int T; std::cin >> T;
    while (T--) {
        int n; std::cin >> n;
        vec<vec<int>> G(n); vec<int> d(n);
        r0p (_, n) {
            int u, v; std::cin >> u >> v, --u, --v;
            G[u].push_back(v), G[v].push_back(u), ++d[u], ++d[v];
        }
        std::queue<int> Q; vec<int> sz(n, 1);
        r0p (u, n) if (d[u] == 1) Q.push(u);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            each (v, G[u]) {
                if (d[v] > 1) sz[v] += sz[u];
                if (--d[v] == 1) Q.push(v);
            }
        }
        auto C2 = [](int x) { return 1ll * x * (x - 1) / 2; };
        ll A = 2ll * C2(n);
        r0p (u, n) if (d[u] > 1) A -= C2(sz[u]);
        std::cout << A << '\n';
    }
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
