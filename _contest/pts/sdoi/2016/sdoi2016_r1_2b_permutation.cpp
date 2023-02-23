/* sdoi2016_r1_2b_permutation.cpp */
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

const int maxn = 1e6 + 5;
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

int fac[maxn], ifac[maxn], f[maxn];
void init(int n) {
    fac[0] = 1; rep (i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
    ifac[n] = inv(fac[n]); per (i, n, 1) ifac[i - 1] = 1ll * ifac[i] * i % mod;
    f[2] = 1; rep (i, 3, n) f[i] = 1ll * (i - 1) * (f[i - 1] + f[i - 2]) % mod;
}
int C(int n, int m) { return n < m ? 0 : 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    init(maxn - 5);
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        cout << (n == m ? 1 : 1ll * C(n, m) * f[n - m] % mod) << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
