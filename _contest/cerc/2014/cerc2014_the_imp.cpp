/* cerc2014_the_imp.cpp */
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

struct opt { int w, c; };

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    const ll inf = ~0ull >> 2;
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        vec<opt> a(n); each (x, a) cin >> x.w >> x.c;
        sort(all(a), [](const opt &x, const opt &y) { return x.w < y.w; });
        a.push_back({0, 0}), reverse(all(a));
        vec<vec<ll>> f(n + 1, vec<ll>(k + 1));
        rep (i, 1, n) f[i][0] = max(f[i - 1][0], ll(a[i].w) - a[i].c);
        rep (i, 1, n) rep (j, 1, k)
            f[i][j] = max(f[i - 1][j], min(f[i - 1][j - 1], ll(a[i].w)) - a[i].c);
        cout << f[n][k] << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
