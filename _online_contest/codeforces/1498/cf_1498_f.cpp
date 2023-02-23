/* cf_1498_f.cpp */
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
    int n, k; cin >> n >> k;
    vec<vec<int>> G(n);
    r0p (_, n - 1) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u);
    }
    vec<int> a(n); each (x, a) cin >> x;
    auto nxt = [&](int x) { return (x + 1) % (2 * k); };
    auto pre = [&](int x) { return (x - 1 + 2 * k) % (2 * k); };
    vec<vec<int>> f(n, vec<int>(2 * k));
    function<void(int, int)> dfs = [&](int u, int fa) {
        f[u][0] = a[u];
        each (v, G[u]) if (v != fa) {
            dfs(v, u);
            r0p (i, 2 * k) f[u][i] ^= f[v][pre(i)];
        }
    };
    dfs(0, -1);
    vec<vec<int>> g = f; vec<int> A(n);
    function<void(int, int)> dfs2 = [&](int u, int fa) {
        r0p (i, k) A[u] ^= g[u][i + k];
        each (v, G[u]) if (v != fa) {
            r0p (i, 2 * k) g[v][nxt(i)] ^= g[u][i] ^ f[v][pre(i)];
            dfs2(v, u);
        }
    };
    dfs2(0, -1);
    r0p (i, n) cout << (A[i] != 0) << ' ';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
