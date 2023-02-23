/* upts2017_problem.cpp */
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, p, k, r; cin >> n >> p >> k >> r;
    auto norm = [&](int &x) {
        if (x >= p) x -= p;
        else if (x < 0) x += p;
    };
    using poly = vec<int>;
    auto mul = [&](const poly &f, const poly &g) {
        poly h(k);
        r0p (i, k) r0p (j, k) norm(h[(i + j) % k] += ll(f[i]) * g[j] % p);
        return h;
    };
    auto qpow = [&](poly a, ll b) {
        poly c(k); c[0] = 1;
        for (; b; b >>= 1, a = mul(a, a)) if (b & 1) c = mul(c, a);
        return c;
    };
    poly f(k);
    if (k == 1) f[0] = 2 % p;
    else f[0] = f[1] = 1;
    cout << qpow(f, ll(n) * k)[r] << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
