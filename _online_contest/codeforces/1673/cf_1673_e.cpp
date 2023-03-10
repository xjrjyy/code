/* cf_1673_e.cpp */
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

const int maxn = (1 << 20) + 5;
const int N = 20;
const int maxN = (1 << 20) + 5;
const int inf = ~0u >> 2;

int n, m, a[maxn], pw[maxN], f[N + 4][maxn], A[1 << N];

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> m;
    rep (i, 1, n) std::cin >> a[i];
    pw[0] = 1; rep (i, 1, 1 << N) pw[i] = std::min(pw[i - 1] * 2, inf);
    rep (i, 0, N + 3) per (j, n - i, 0) f[i][j] = f[i][j + 1] ^ ((j & (n - i)) == j);
    rep (L, 1, n) {
        ll t = 0;
        rep (R, L, std::min(L + N, n)) {
            t = (R == L ? a[R] : t * pw[a[R]]);
            if (t >= (1 << N)) break;
            int p = (L != 1) + (R != n), q = 1 + (R - L) + p;
            A[t] ^= f[q][std::max(0, m - p)];
        }
    }
    int p = 1 << N;
    while (p--) if (A[p]) break;
    std::cout << A[p];
    while (p-- > 0) std::cout << A[p];
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
