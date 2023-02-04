/* ioi2022_1b_rarest_insects.cpp */
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

std::vector<std::vector<int>> devise_strategy(int n) {
    vec<vec<int>> A;
    const vec<int> kDiv = {3, 3, 3, 3, 2, 2, 2, 2};
    auto set = [&](int p, int q, int x) {
        while (int(A.size()) <= p) A.push_back(vec<int>(n + 1));
        A[p][q] = x;
    };
    function<void(int, int, int, int, int)> bld = [&](int k, int t, int l, int r, int p) {
        int u = k & 1;
        set(t, 0, u), set(t, l, -(u + 1)), set(t, r, -(!u + 1));
        ++l, --r; if (l > r) return;
        auto hold = [&](int T, int L, int R) {
            if (L > R) return;
            rep (i, l - 1, r + 1) if (i < L || i > R) set(T, i, i < L ? -(!u + 1) : -(u + 1));
            rep (i, L, R) set(t, i, T);
            bld(k + 1, T, L, R, p + kDiv[k]);
        };
        if (kDiv[k] == 3) {
            int m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
            hold(p, l, m1), hold(p + 1, m1 + 1, m2 - 1), hold(p + 2, m2, r);
        } else {
            int m = (l + r) / 2;
            hold(p, l, m), hold(p + 1, m + 1, r);
        }
    };
    bld(0, 0, 1, n, 1);
    return A;
}
