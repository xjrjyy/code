/* cf_1214_h.cpp */
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
    vec<int> fa(n, -1), dp(n);
    function<void(int)> dfs = [&](int u) {
        each (v, G[u]) if (v != fa[u]) fa[v] = u, dp[v] = dp[u] + 1, dfs(v);
    };
    dfs(0);
    int s = max_element(all(dp)) - dp.begin();
    fa[s] = -1, dp[s] = 0, dfs(s);
    int t = max_element(all(dp)) - dp.begin();
    cerr << s << ' ' << t << '\n';
    vec<int> A(n);
    auto prt = [&]() {
        cout << "Yes\n";
        each (x, A) cout << ((x % k) + k) % k + 1 << ' ';
    };
    if (k == 2) {
        r0p (u, n) A[u] = dp[u] & 1;
        return prt(), 0;
    }
    vec<int> a(n);
    {
        int u = t;
        while (~u) a[u] = 1, u = fa[u];
    }
    function<void(int, int, int)> dfs2 = [&](int u, int d, int o) {
        if (!a[u] && d >= k - 1) cout << "No\n", exit(0);
        each (v, G[u]) if (v != fa[u]) {
            int w = d ? d + 1 : 0, r = o;
            if (!a[v] && !d) {
                int p = dp[u], q = dp[t] - dp[u];
                w = min(p, q) + 1, r = (p > q ? 1 : -1);
                cerr << u << ' ' << v << ' ' << p << ' ' << q << '\n';
            }
            A[v] = A[u] + r, dfs2(v, w, r);
        }
    };
    dfs2(s, 0, 1);
    prt();
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
