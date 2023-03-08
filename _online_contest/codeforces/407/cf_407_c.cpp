/* cf_407_c.cpp */
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

const int maxn = 1e5 + 5;
const int maxk = 1e2 + 5;
const int P = 1e9 + 7;

int &fix(int &x) {
    if (x >= P) x -= P;
    if (x < 0) x += P;
    return x;
}

int n, m = 100, q, a[maxk][maxn], b[maxn], s[maxk][maxn];

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> q;
    rep (i, 1, n) std::cin >> b[i];
    s[0][1] = 1;
    rep (i, 1, m + 2) rep (j, 1, n) fix(s[i][j] = s[i][j - 1] + s[i - 1][j]);
    r0p (_, q) {
        int l, r, k; std::cin >> l >> r >> k;
        fix(a[k + 1][l] += 1);
        rep (i, 1, k + 1) fix(a[i][r + 1] -= s[k - i + 2][r - l + 1]);
    }
    per (i, m + 1, 1) rep (j, 1, n) fix(a[i - 1][j] += fix(a[i][j] += a[i][j - 1]));
    rep (i, 1, n) std::cout << fix(b[i] += a[0][i]) << ' ';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
