/* luogu_p8321.cpp */
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

const int mod = 998244353;
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

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vec<int> a(n); each (x, a) cin >> x;
    vec<int> b(n); each (x, b) cin >> x;
    sort(all(b), greater<int>());
    vec<int> c, d;
    for (int i = 0, j = 0; i < n || j < n; ) {
        if (j >= n || (i < n && a[i] >= b[j])) c.push_back(a[i++]), d.push_back(j);
        else c.push_back(b[j++]), d.push_back(i);
    }
    vec<vec<int>> f(2 * n + 1, vec<int>(n + 1));
    f[0][0] = 1;
    rep (i, 1, 2 * n) rep (j, 0, n) {
        f[i][j] = f[i - 1][j];
        if (j) norm(f[i][j] += ll(f[i - 1][j - 1]) * c[i] % mod * (d[i] - (j - 1)) % mod);
    }
    int t = 1; rep (i, 1, n) t = ll(t) * i % mod;
    cout << ll(f[2 * n][n]) * inv(t) % mod << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
