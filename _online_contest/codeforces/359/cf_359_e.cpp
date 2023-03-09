/* cf_359_e.cpp */
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
    const vec<int> Dx = {0, 0, -1, 1}, Dy = {-1, 1, 0, 0};
    const std::string msg = "LRUD12";
    int n, m = 0, p, q; std::cin >> n >> p >> q, --p, --q;
    vec<vec<int>> a(n, vec<int>(n)); each (x, a) each (y, x) std::cin >> y, m += y;
    vec<int> A;
    auto add = [&]() { A.push_back(4); };
    auto del = [&]() { A.push_back(5); };
    auto mov = [&](int t) { A.push_back(t); };
    auto id = [&](int x, int y) { return x * n + y; };
    auto in = [&](int x, int y) { return 0 <= x && x < n && 0 <= y && y < n; };
    vec<vec<int>> b(n, vec<int>(n)); vec<std::array<int, 4>> G(n * n, {-1, -1, -1, -1});
    std::function<void(int, int)> dfs = [&](int x, int y) {
        b[x][y] = 1; if (!a[x][y]) add(), a[x][y] = 1, ++m;
        r0p (_, 4) {
            int u = x + Dx[_], v = y + Dy[_];
            if (!in(u, v) || b[u][v]) continue;
            bool o = false;
            while (!o && in(u, v)) o |= a[u][v], u += Dx[_], v += Dy[_];
            if (o) {
                G[id(x, y)][_] = id(u = x + Dx[_], v = y + Dy[_]);
                mov(_), dfs(u, v), mov(_ ^ 1);
            }
        }
    };
    std::function<void(int, int)> dfs2 = [&](int x, int y) {
        r0p (_, 4) if (~G[id(x, y)][_]) {
            int w = G[id(x, y)][_], u = w / n, v = w % n;
            mov(_), dfs2(u, v), mov(_ ^ 1);
        }
        if (a[x][y]) del(), a[x][y] = 0, --m;
    };
    dfs(p, q), dfs2(p, q);
    if (m) return std::cout << "NO\n", 0;
    std::cout << "YES\n";
    each (x, A) std::cout << msg[x];
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
