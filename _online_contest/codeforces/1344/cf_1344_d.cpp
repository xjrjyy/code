/* cf_1344_d.cpp */
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

ll G(int x, int y) { return -3ll * x * x - 3ll * x - 1 + y; }

int n, a[maxn], b[maxn], c[maxn]; ll m, p;

bool chk(ll o) {
    ll t = 0;
    rep (i, 1, n) {
        int L = 0, R = a[i], M, A = 0;
        while (L <= R) {
            if (G((M = (L + R) / 2) - 1, a[i]) >= o) A = M, L = M + 1;
            else R = M - 1;
        }
        t += A, c[i] = A;
    }
    if (t < m) p = t, std::copy(c + 1, c + n + 1, b + 1);
    return t < m;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> m;
    rep (i, 1, n) std::cin >> a[i];
    ll L = -4e18, R = 4e18, M, A = 0;
    while (L <= R) {
        if (chk(M = (L + R) / 2)) A = M, R = M - 1;
        else L = M + 1;
    }
    rep (i, 1, n) while (p < m && b[i] < a[i] && G(b[i], a[i]) == A - 1) ++p, ++b[i];
    rep (i, 1, n) std::cout << b[i] << ' ';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
