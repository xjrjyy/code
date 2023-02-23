/* cf_1626_e.cpp */
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
    int n; cin >> n;
    vec<int> a(n); each (x, a) cin >> x;
    vec<vec<int>> G(n);
    r0p (_, n - 1) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u);
    }
    vec<int> f(n), s(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
        f[u] = a[u], s[u] = a[u];
        each (v, G[u]) if (v != fa) {
            dfs(v, u), s[u] += s[v];
            f[u] |= (a[v] || (f[v] && s[v] > 1));
        }
    };
    function<void(int, int)> dfs2 = [&](int u, int fa) {
        each (v, G[u]) if (v != fa) {
            f[v] |= (a[u] || (f[u] && s[u] - s[v] > 1));
            s[v] += s[u] - s[v];
            dfs2(v, u);
        }
    };
    dfs(0, -1), dfs2(0, -1);
    each (x, f) cout << x << ' ';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
