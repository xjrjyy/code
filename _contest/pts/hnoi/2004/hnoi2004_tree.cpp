/* hnoi2004_tree.cpp */
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
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vec<int> a(n); each (x, a) cin >> x, --x;
    if (n == 1 && a[0] == -1) return cout << 1 << '\n', 0; 
    if (accumulate(all(a), 0) != n - 2) return cout << 0 << '\n', 0;
    if (any_of(all(a), [](int x) { return x < 0; })) return cout << 0 << '\n', 0;
    auto qpow = [&](int a, int b, int mod) {
        int c = 1;
        for (; b; b >>= 1, a = ll(a) * a % mod) if (b & 1) c = ll(c) * a % mod;
        return c;
    };
    auto inv = [&](int x, int mod) { return qpow(x, mod - 2, mod); };
    auto solve = [&](int mod) {
        vec<int> f(n);
        r0p (i, n) f[i] = (i ? ll(f[i - 1]) * i % mod : 1);
        int p = f[n - 2], q = 1;
        r0p (u, n) q = ll(q) * f[a[u]] % mod;
        return ll(p) * inv(q, mod) % mod;
    };
    int P = 998244353, Q = 1000000007;
    int X = solve(P), Y = solve(Q);
    ll A = (ll(X) * inv(Q, P) % P * Q + ll(Y) * inv(P, Q) % Q * P) % (ll(P) * Q);
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
