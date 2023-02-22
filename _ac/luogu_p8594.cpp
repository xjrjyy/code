/* luogu_p8594.cpp */
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

const int maxn = 4e7 + 5;
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

int fc[maxn], ifc[maxn];
void init(int n) {
    fc[0] = 1; rep (i, 1, n) fc[i] = 1ll * fc[i - 1] * i % mod;
    ifc[n] = inv(fc[n]); per (i, n, 1) ifc[i - 1] = 1ll * ifc[i] * i % mod;
}
int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m; cin >> n >> m, init(max(2 * n, m + 1));
    int A = (n == m);
    rep (i, 0, m) rep (j, 0, m)
        norm(A += 1ll * C(i + 1, j) * C(2 * (n - i - j), m - i - 2 * j) % mod * C(n - i - 1, j - 1) % mod);
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
