/* cf_1750_f.cpp */
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

const int maxn = 5e3 + 5;

int f[maxn], g[maxn][2 * maxn][2], h[maxn][2 * maxn], s[2 * maxn][maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, mod; cin >> n >> mod;
    if (n == 1) return cout << 1 << '\n', 0;
    auto norm = [&](int &x) {
        if (x >= mod) x -= mod;
        else if (x < 0) x += mod;
    };
    f[0] = f[1] = 1, f[2] = 2;
    rep (i, 3, n) f[i] = (f[i - 1] * 2) % mod;
    g[1][1 + n][1] = s[2][1] = s[2][2] = 1;
    auto qry = [&](const int *v, int l, int r) {
        return v[r] - (l ? v[l - 1] : 0);
    };
    rep (i, 2, n) {
        auto in = [&](int x) { return 0 <= x && x <= n; };
        rep (j, -i, i) {
            norm(g[i][j + n][0] += qry(s[i - j], i - (i + j) / 2, min(i - j, i - 1)));
            if (j > 0) norm(g[i][j + n][1] += ll(qry(h[i - j], j + 1 + n, i + n)) * f[j] % mod);
            norm(f[i] = (f[i] - g[i][j + n][0] - g[i][j + n][1]) % mod);
        }
        g[i][i + n][1] = f[i];
        rep (j, -n, n) norm(h[i][j + n] = g[i][j + n][0] + (j + n ? h[i][j + n - 1] : 0));
        rep (j, -i, i) norm(s[i + j][i] = g[i][j + n][1] + s[i + j][i - 1]);
    }
    cout << f[n] << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
