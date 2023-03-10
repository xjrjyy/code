/* cf_1474_e.cpp */
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

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T; std::cin >> T;
    while (T--) {
        int n; std::cin >> n;
        vec<int> a(n); std::iota(all(a), 1);
        vec<std::pair<int, int>> A; ll B = 0;
        auto push = [&](int i, int j) {
            if (i == j) return;
            A.push_back({i + 1, j + 1});
            B += 1ll * (i - j) * (i - j), std::swap(a[i], a[j]);
        };
        push(n - 1, 0);
        rep (i, 1, (n - 1) / 2) push(n - 1 - i, 0);
        rep (i, 1, (n - 2) / 2) push(i, n - 1);
        std::reverse(all(A));
        std::cout << B << '\n';
        each (x, a) std::cout << x << ' ';
        std::cout << '\n' << A.size() << '\n';
        each (x, A) std::cout << x.first << ' ' << x.second << '\n';
    }
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
