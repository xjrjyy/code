/* cf_1080_e.cpp */
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

const int mod = 1011451423;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m; std::cin >> n >> m;
    vec<std::string> a(n); each (x, a) std::cin >> x;
    ll A = 0;
    auto sol = [&](const vec<int> &s) {
        int n = int(s.size()); vec<int> t(n);
        int l = 0, r = -1, k;
        r0p (i, n) {
            k = std::max(0, std::min(r - i, t[l + (r - i)]));
            while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k;
            t[i] = k, A += k / 2;
            if (i + k > r) l = i - k, r = i + k;
        }
    };
    vec<int> H(26, 1); rep (i, 1, 25) H[i] = 1145141ll * H[i - 1] % mod;
    vec<int> h(n), d(n); vec<std::array<int, 26>> b(n);
    auto add = [&](int i, int c) {
        h[i] = (h[i] + H[c]) % mod;
        d[i] -= b[i][c], b[i][c] ^= 1, d[i] += b[i][c];
    };
    r0p (L, m) {
        r0p (i, n) h[i] = 1, d[i] = 0, std::fill(all(b[i]), 0);
        rep (R, L, m - 1) {
            r0p (i, n) add(i, a[i][R] - 'a');
            for (int l = 0, r; l < n; l = r + (d[r] > 1)) {
                r = l; while (r < n && d[r] <= 1) ++r;
                if (l < r) {
                    vec<int> s{-1};
                    rep (i, l, r - 1) s.push_back(h[i]), s.push_back(-1);
                    sol(s);
                }
            }
        }
    }
    std::cout << A << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
