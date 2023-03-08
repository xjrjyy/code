/* upts2021_ranklist.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = (l), rep##i = (r); i <= rep##i; ++i)
#define per(i, r, l) for (int i = (r), per##i = (l); i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : (s))
#define all(s) (s).begin(), (s).end()
#define dbg(x) (std::cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << std::endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>;

const int maxn = 13 + 5;
const int maxU = (1 << 13) + 5;
const int maxm = 5e2 + 5;

int n, m, U, a[maxn], b[maxn][maxn], sz[maxU], f[maxU][maxn][maxm]; ll A;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> m, U = (1 << n) - 1; int p = 0;
    r0p (i, n) std::cin >> a[i], p = (a[i] > a[p] ? i : p);
    r0p (i, n) r0p (j, n) if (a[i] <= a[j]) b[i][j] = a[j] - a[i] + (i > j);
    r0p (i, n) if (b[i][p] * n <= m) f[1 << i][i][b[i][p] * n] = 1;
    rep (S, 1, U) sz[S] = sz[S >> 1] + (S & 1);
    rep (S, 1, U) r0p (i, n) if ((S >> i) & 1) r0p (k, n) if (~(S >> k) & 1) {
        int w = b[k][i] * (n - sz[S]);
        rep (j, 0, m - w) f[S | (1 << k)][k][w + j] += f[S][i][j];
    }
    r0p (i, n) rep (j, 0, m) A += f[U][i][j];
    std::cout << A << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
