/* cf_739_e.cpp */
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

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    const double eps = 1e-8;
    int n, m, q; cin >> n >> m >> q;
    vec<double> a(n + 1), b(n + 1);
    rep (i, 1, n) cin >> a[i];
    rep (i, 1, n) cin >> b[i];
    auto chk = [&](double o) {
        vec<vec<double>> f(n + 1, vec<double>(m + 1));
        vec<vec<int>> g(n + 1, vec<int>(m + 1));
        rep (i, 1, n) rep (j, 0, m) {
            f[i][j] = -1;
            auto upd = [&](int x, int y, double w, int t) {
                w += f[x][y], t += g[x][y];
                if (f[i][j] < w) f[i][j] = w, g[i][j] = t;
            };
            upd(i - 1, j, 0, 0);
            if (j) upd(i - 1, j - 1, a[i], 0);
            upd(i - 1, j, b[i] - o, 1);
            if (j) upd(i - 1, j - 1, a[i] + b[i] - a[i] * b[i] - o, 1);
        }
        int p = max_element(all(f[n])) - f[n].begin();
        return make_pair(f[n][p], g[n][p]);
    };
    double L = 0, R = 1, M, A;
    while (R - L >= eps) {
        auto t = chk(M = (L + R) / 2); A = t.first;
        if (t.second < q) R = M;
        else L = M;
    }
    cout << fixed << setprecision(4) << A + M * q << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
