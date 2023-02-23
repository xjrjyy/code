/* cf_1391_e.cpp */
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
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vec<vec<int>> G(n);
        r0p (_, m) {
            int u, v; cin >> u >> v, --u, --v;
            G[u].push_back(v), G[v].push_back(u);
        }
        vec<int> d(n, -1), fa(n, -1); vec<vec<int>> p(n);
        function<void(int)> dfs = [&](int u) {
            p[d[u]].push_back(u);
            each (v, G[u]) if (!~d[v]) d[v] = d[u] + 1, fa[v] = u, dfs(v);
        };
        d[0] = 0, dfs(0);
        if (*max_element(all(d)) >= (n + 1) / 2) {
            cout << "PATH\n" << (n + 1) / 2 << '\n';
            int s = max_element(all(d)) - d.begin();
            r0p (_, (n + 1) / 2) cout << s + 1 << ' ', s = fa[s];
            cout << '\n';
        } else {
            vec<pair<int, int>> A;
            each (t, p) for (int i = 0; i + 1 < int(t.size()); i += 2)
                A.push_back({t[i], t[i + 1]});
            cout << "PAIRING\n" << A.size() << '\n';
            each (x, A) cout << x.first + 1 << ' ' << x.second + 1 << '\n';
        }
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
