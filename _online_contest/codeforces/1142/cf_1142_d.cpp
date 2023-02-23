/* cf_1142_d.cpp */
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
    string s; cin >> s;
    int n = int(s.size());
    vec<ll> f(11), g(11); ll A = 0;
    each (c, s) {
        int x = c - '0';
        g = f, fill(all(f), 0);
        rep (i, x + 1, 10) f[(x + 10 + i * (i - 1) / 2) % 11] += g[i];
        if (x) f[x] += 1;
        A += accumulate(all(f), 0ll);
    }
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
