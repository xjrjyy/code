/* luogu_p4240.cpp */
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

const int maxn = 1e5 + 5;
const int mod = 998244353;
const int B = 45;
void norm(int &x) {
    assert(-mod <= x && x < 2 * mod);
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}
int qpow(int a, int b) {
    int c = 1;
    for (; b; b >>= 1, a = ll(a) * a % mod) if (b & 1) c = ll(c) * a % mod;
    return c;
}
int inv(int x) { return qpow(x, mod - 2); }

int vs[maxn]; vec<int> P;
int mu[maxn], ph[maxn], f[maxn]; vec<int> g[maxn]; int h[B + 1][B + 1][maxn];
void init(int n) {
    mu[1] = ph[1] = f[1] = 1;
    rep (i, 2, n) {
        if (!vs[i]) P.push_back(i), mu[i] = -1, ph[i] = i - 1, f[i] = inv(i - 1);
        each (p, P) {
            if (i * p > n) break;
            vs[i * p] = 1;
            if (i % p == 0) {
                mu[i * p] = 0, ph[i * p] = ph[i] * p, f[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i], ph[i * p] = ph[i] * (p - 1), f[i * p] = ll(f[i]) * f[p] % mod;
        }
    }
    g[0].resize(n + 1);
    rep (i, 1, n) {
        g[i].resize(n / i + 1);
        rep (j, 1, n / i) norm(g[i][j] = g[i - 1][j] + ph[i * j]);
    }
    rep (i, 1, B) rep (j, 1, B) rep (k, 1, n / max(i, j))
        norm(h[i][j][k] = h[i][j][k - 1] + ll(f[k]) * g[i][k] % mod * g[j][k] % mod);
}

void solve() {
    int n, m, A = 0; cin >> n >> m; if (n > m) swap(n, m);
    int l, r;
    for (l = m / B + 1; l <= n; l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        int p = n / l, q = m / l;
        norm(A += h[p][q][r] - h[p][q][l - 1]);
    }
    rep (i, 1, m / B) norm(A += ll(f[i]) * g[n / i][i] % mod * g[m / i][i] % mod);
    cout << A << '\n';
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    init(1e5);
    int T; cin >> T;
    while (T--) solve();
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
