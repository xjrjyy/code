/* haoi2018_color.cpp */
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

const int maxn = 1e7 + 5;
const int maxm = 3.3e5 + 5;
const int mod = 1004535809;
const int _G = 3;
const int iG = mod / _G + 1;

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

int fac[maxn], ifac[maxn];
void init(int n) {
    rep (i, 0, n) fac[i] = (i ? ll(fac[i - 1]) * i % mod : 1);
    ifac[n] = inv(fac[n]);
    per (i, n, 1) ifac[i - 1] = ll(ifac[i]) * i % mod;
}
int C(int n, int m) { return n < m ? 0 : ll(fac[n]) * ifac[m] % mod * ifac[n - m] % mod; }

int n, N, m, M, k, a[maxm], f[maxm], g[maxm], T[maxm], W[maxm], A;

void NTT(int *f, int n, int rev) {
    r0p (i, n) if (i < T[i]) swap(f[i], f[T[i]]);
    for (int l = 1; l < n; l <<= 1) {
        int w = qpow(~rev ? _G : iG, (mod - 1) / l / 2);
        r0p (i, l) W[i] = (i ? ll(W[i - 1]) * w % mod : 1);
        for (int p = 0; p < n; p += 2 * l) {
            for (int i = 0; i < l; ++i) {
                int t = ll(f[p + l + i]) * W[i] % mod;
                norm(f[p + l + i] = f[p + i] - t);
                norm(f[p + i] += t);
            }
        }
    }
    if (!~rev) { int t = inv(n); r0p (i, n) f[i] = ll(f[i]) * t % mod; }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    init(maxn - 5);
    cin >> n >> m >> k, N = 1, M = min(m, n / k) + 1;
    rep (i, 0, m) cin >> a[i];
    r0p (i, M) {
        f[i] = ll(C(n, i * k)) * C(m, i) % mod * qpow(m - i, n - i * k) % mod
            * fac[i * k] % mod * inv(qpow(fac[k], i)) % mod;
        f[i] = ll(f[i]) * fac[i] % mod, norm(g[i] = (i & 1 ? -ifac[i] : ifac[i]));
    }
    reverse(f, f + M);
    while (N < M * 2) N <<= 1;
    r0p (i, N) T[i] = (T[i >> 1] + (i & 1) * N) >> 1;
    NTT(f, N, 1), NTT(g, N, 1);
    r0p (i, N) f[i] = ll(f[i]) * g[i] % mod;
    NTT(f, N, -1);
    reverse(f, f + M);
    r0p (i, M) norm(A += ll(f[i]) * a[i] % mod * ifac[i] % mod);
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
