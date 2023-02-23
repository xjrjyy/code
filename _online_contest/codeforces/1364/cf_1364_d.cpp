/* cf_1364_d.cpp */
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
    int n, N, m, k, q; cin >> n >> m >> k, N = ceil(log2(n)) + 1, q = (k + 1) / 2;
    vec<vec<int>> G(n);
    r0p (_, m) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u);
    }
    vec<int> d(n, -1), fa(n);
    function<void(int)> dfs = [&](int u) {
        each (v, G[u]) if (v != fa[u]) {
            if (!~d[v]) {
                d[v] = d[u] + 1, fa[v] = u, dfs(v);
            } else if (d[u] > d[v] && d[u] - d[v] + 1 <= k) {
                cout << 2 << '\n' << d[u] - d[v] + 1 << '\n';
                while (u != v) cout << u + 1 << ' ', u = fa[u];
                cout << v + 1, exit(0);
            }
        }
    };
    d[0] = 0, dfs(0);
    vec<int> A;
    if (m == n - 1) {
        int t = (count_if(all(d), [](int x) { return x & 1; }) >= q);
        r0p (i, n) if ((d[i] & 1) == t) A.push_back(i);
    } else {
        int s = max_element(all(d)) - d.begin();
        r0p (_, q) A.push_back(s), s = fa[fa[s]];
    }
    cout << 1 << '\n';
    r0p (i, q) cout << A[i] + 1 << ' ';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
