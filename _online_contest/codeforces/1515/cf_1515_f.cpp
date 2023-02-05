/* cf_1515_f.cpp */
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
    int n, m, x; cin >> n >> m >> x;
    vec<ll> a(n); each (x, a) cin >> x;
    if (accumulate(all(a), 0ll) < ll(n - 1) * x) return cout << "NO\n", 0;
    vec<vec<pair<int, int>>> G(n);
    r0p (i, m) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back({v, i}), G[v].push_back({u, i});
    }
    vec<int> vs(n), A, B;
    function<void(int)> dfs = [&](int u) {
        vs[u] = 1;
        each (e, G[u]) {
            int v = e.first, w = e.second; if (vs[v]) continue;
            dfs(v);
            if (a[v] >= x) A.push_back(w), a[u] = a[u] + a[v] - x;
            else B.push_back(w);
        }
    };
    dfs(0);
    reverse(all(B));
    cout << "YES\n";
    each (x, A) cout << x + 1 << '\n';
    each (x, B) cout << x + 1 << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
