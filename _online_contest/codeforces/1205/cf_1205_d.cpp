/* cf_1205_d.cpp */
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
    vec<vec<int>> G(n);
    r0p (_, n - 1) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u);
    }
    vec<int> sz(n), fa(n, -1); int S = -1;
    function<void(int)> dfs = [&](int u) {
        sz[u] = 1; int mx = 0;
        each (v, G[u]) if (v != fa[u]) fa[v] = u, dfs(v), sz[u] += sz[v], mx = max(mx, sz[v]);
        if (max(mx, n - sz[u]) <= n / 2) S = u;
    };
    dfs(0), fa[S] = -1, dfs(S);
    vec<int> A(n); int tt = 0, o = 1;
    function<void(int)> col = [&](int u) {
        A[u] = o * ++tt;
        each (v, G[u]) if (v != fa[u]) col(v);
    };
    sort(all(G[S]), [&](int x, int y) { return sz[x] < sz[y]; });
    A[S] = 0;
    each (u, G[S]) {
        col(u);
        if (tt > (n - 1) / 3) o = tt, tt = 0;
    }
    r0p (u, n) if (u != S) {
        int v = fa[u], w = A[u] - A[v];
        cout << u + 1 << ' ' << v + 1 << ' ' << w << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
