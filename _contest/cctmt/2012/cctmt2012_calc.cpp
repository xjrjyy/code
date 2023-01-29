/* cctmt2012_calc.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : s)
#define all(s) (s).begin(), (s).end()
#define dbg(x) (cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>; using namespace std;

const int maxn = 1e3 + 5;
int mod;

void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}
int qpow(int a, int b) {
    int c = 1;
    for (; b; b >>= 1, a = ll(a) * a % mod) if (b & 1) c = ll(c) * a % mod;
    return c;
}
int inv(int x) { return qpow(x, mod - 2); }

int n, f[maxn][maxn], g[maxn];

int Lag(int x, int *f, int n) {
    if (x <= n) return f[x];
    int y = 0;
    rep (i, 0, n) {
        int p = 1, q = 1;
        rep (j, 0, n) if (j != i) p = ll(p) * (x - j) % mod;
        rep (j, 0, n) if (j != i) q = ll(q) * (i - j) % mod;
        norm(p), norm(q);
        norm(y += ll(f[i]) * p % mod * inv(q) % mod);
    }
    return y;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int x, y = 1;
    cin >> x >> n >> mod;
    rep (i, 0, 2 * n) f[0][i] = 1;
    rep (i, 1, n) rep (j, 1, 2 * n)
        norm(f[i][j] = ll(f[i - 1][j - 1]) * j % mod + f[i][j - 1]);
    rep (i, 0, 2 * n) g[i] = f[n][i];
    rep (i, 1, n) y = ll(y) * i % mod;
    cout << ll(y) * Lag(x, g, 2 * n) % mod << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
