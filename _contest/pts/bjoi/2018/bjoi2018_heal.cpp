/* bjoi2018_heal.cpp */
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

const int maxn = 1.5e3 + 5;
const int mod = 1e9 + 7;

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

int n, p, m, k, a[maxn][maxn], w[maxn];

void Gauss() {
    rep (i, 1, n) {
        int r = inv(a[i][i]);
        rep (j, i + 1, n) {
            int t = ll(a[j][i]) * r % mod;
            auto del = [&](int k) { norm(a[j][k] -= ll(t) * a[i][k] % mod); };
            del(i), del(i + 1), del(n + 1);
        }
    }
    per (i, n, 1) {
        a[i][n + 1] = ll(a[i][n + 1]) * inv(a[i][i]) % mod;
        norm(a[i - 1][n + 1] -= ll(a[i - 1][i]) * a[i][n + 1] % mod);
    }
}

void solve() {
    cin >> n >> p >> m >> k;
    if (!k) return cout << -1 << "\n", void();
    if (!m) {
        if (k == 1 && n > 1) return cout << -1 << "\n", void();
        for (; p > 0; p += (p < n) - k) ++m;
        return cout << m << "\n", void();
    }
    int x = inv(m + 1), y = ll(x) * m % mod;
    *w = qpow(y, k), y = inv(y);
    rep (i, 1, min(n + 1, k)) w[i] = ll(w[i - 1]) * (k - i + 1) % mod * inv(i) % mod * x % mod * y % mod;
    w[min(n + 1, k) + 1] = 0, y = ll(x) * m % mod;
    auto W = [&](int i, int j) -> int {
        if (i - j < -1 || i - j > k) return 0;
        if (i == n) return w[i - j];
        return ll(x) * (w[i - j + 1] + (j <= i ? ll(m) * w[i - j] % mod : 0ll)) % mod;
    };
    rep (i, 1, n) rep (j, 1, n) a[i][j] = W(i, j);
    rep (i, 1, n) norm(a[i][i] += -1), a[i][n + 1] = mod - 1;
    Gauss();
    cout << a[p][n + 1] << "\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
