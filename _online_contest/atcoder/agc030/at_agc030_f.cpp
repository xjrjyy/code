/* at_agc030_f.cpp */
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

const int maxn = 6e2 + 5;
const int mod = 1e9 + 7;

void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}

int n, m, a[maxn], b[maxn], c[maxn], vs[maxn], f[maxn][maxn], g[maxn][maxn];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    rep (i, 1, 2 * n) cin >> a[i];
    rep (i, 1, n) if (~a[i * 2 - 1] && ~a[i * 2]) b[a[i * 2 - 1]] = b[a[i * 2]] = 1;
    rep (i, 1, 2 * n) c[i] = c[i - 1] + !b[i];
    rep (i, 1, 2 * n) if (~a[i] && !b[a[i]]) vs[c[a[i]]] = 1, --m;
    m += (n = c[2 * n] / 2);
    f[0][0] = 1;
    rep (i, 1, m) f[0][0] = ll(f[0][0]) * i % mod;
    per (i, 2 * n, 1) {
        rep (j, 0, n) rep (k, 0, n - j) g[j][k] = 0;
        rep (j, 0, n) rep (k, 0, n - j) if (f[j][k]) {
            if (vs[i]) {
                if (j) norm(g[j - 1][k] += f[j][k]);
                if (j + k < n) norm(g[j][k + 1] += f[j][k]);
            } else {
                if (j) norm(g[j - 1][k] += f[j][k]);
                if (k) norm(g[j][k - 1] += ll(f[j][k]) * k % mod);
                if (j + k < n) norm(g[j + 1][k] += f[j][k]);
            }
        }
        swap(f, g);
    }
    cout << f[0][0] << "\n";
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
