/* cf_936_d.cpp */
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
    int n, m[2], t; cin >> n >> m[0] >> m[1] >> t;
    array<vec<int>, 2> a; vec<int> b{0, n + 1};
    r0p (i, 2) {
        a[i].resize(m[i]);
        each (x, a[i]) cin >> x, b.push_back(x), b.push_back(x + 1);
    }

    sort(all(b)), b.erase(unique(all(b)), b.end());
    int N = int(b.size());
    auto Id = [&](int &x) { x = lower_bound(all(b), x) - b.begin(); };
    vec<array<int, 2>> c(N);
    r0p (i, 2) each (x, a[i]) Id(x), c[x][i] = 1;

    vec<array<int, 2>> f(N, {-1, -1}), g(N);
    f[0][0] = f[0][1] = 0;
    rep (i, 1, N - 1) {
        r0p (j, 2) {
            auto upd = [&](int k) {
                int v = f[i - 1][j ^ k];
                if (!~v || (i - 1 && !v)) return;
                if (k) v = min(v, t);
                v += b[i] - b[i - 1];
                if (c[i][j]) v -= t;
                if (v && f[i][j] < v) f[i][j] = v, g[i][j] = k;
            };
            upd(0);
            if (!c[i - 1][j]) upd(1);
        }
    }
    int u = -1; r0p (i, 2) if (~f[N - 1][i]) u = i;
    if (!~u) return cout << "No\n", 0;
    cout << "Yes\n";

    vec<int> F(N), G(N); F[N - 1] = u;
    per (i, N - 1, 1) G[i - 1] = g[i][F[i]], F[i - 1] = F[i] ^ G[i - 1];
    vec<int> A; vec<pair<int, int>> B;
    if (F[0]) A.push_back(0);
    rep (i, 1, N - 1) if (G[i]) A.push_back(b[i]);

    int o = ~0u >> 2;
    p0r (i, N - 1) if (c[i][F[i]]) {
        o = min(o - t, b[i] - 1);
        B.push_back({o, F[i]});
    }
    reverse(all(B));
    cout << A.size() << '\n';
    each (x, A) cout << x << ' ';
    cout << '\n';
    cout << B.size() << '\n';
    each (x, B) cout << x.first << ' ' << x.second + 1 << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
