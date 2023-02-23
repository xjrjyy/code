/* cf_1534_d.cpp */
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
    int n, m; cin >> n;
    auto qry = [&](int u) {
        cout << "? " << u + 1 << endl;
        vec<int> a(n); each (x, a) cin >> x;
        return a;
    };
    vec<int> fa(n), d(n), c(2);
    auto upd = [&](int u) {
        auto t = qry(u);
        r0p (v, n) if (t[v] == 1) {
            if (d[v] < d[u]) fa[u] = v;
            else fa[v] = u;
        }
    };
    d = qry(0), m = *max_element(all(d));
    vec<vec<int>> p(m + 1);
    r0p (i, n) ++c[d[i] & 1], p[d[i]].push_back(i);
    --c[0]; int k = c[0] > c[1];
    for (int i = 2 - k; i <= m; i += 2) each (u, p[i]) upd(u);
    cout << "!\n";
    rep (i, 1, n - 1) cout << fa[i] + 1 << ' ' << i + 1 << '\n';
    cout << endl;
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
