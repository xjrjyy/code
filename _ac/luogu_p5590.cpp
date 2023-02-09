/* luogu_p5590.cpp */
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
    const int inf = ~0u >> 2;
    int n, m; cin >> n >> m;
    vec<vec<pair<int, int>>> G(n), R(n); vec<pair<int, int>> E;
    r0p (i, m) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back({v, i}), R[v].push_back({u, i}), E.push_back({u, v});
    }
    vec<int> a(n), b(n);
    function<void(int)> dfs = [&](int u) {
        a[u] = 1; each (p, G[u]) if (!a[p.first]) dfs(p.first);
    };
    function<void(int)> dfs2 = [&](int u) {
        b[u] = 1; each (p, R[u]) if (!b[p.first]) dfs2(p.first);
    };
    dfs(0), dfs2(n - 1); r0p (u, n) a[u] &= b[u];
    if (!a[0] || !a[n - 1]) return cout << -1 << '\n', 0;
    auto rmv = [&](vec<pair<int, int>> &G) {
        return G.erase(remove_if(all(G), [&](const pair<int, int> &p) {
            return !a[p.first];
        }), G.end());
    };
    r0p (u, n) if (a[u]) rmv(G[u]), rmv(R[u]);
    auto topo = [&]() {
        vec<int> d(n); queue<int> Q;
        r0p (u, n) if (a[u]) each (p, G[u]) ++d[p.first];
        r0p (u, n) if (a[u] && !d[u]) Q.push(u);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            each (p, G[u]) if (!--d[p.first]) Q.push(p.first);
        }
        return !d[n - 1];
    };
    if (!topo()) return cout << -1 << '\n', 0;
    int N = 2 * n;
    vec<vec<pair<int, int>>> g(N);
    auto add = [&](int u, int v, int w) {
        g[u].push_back({v, w});
    };
    auto spfa = [&](int s, vec<int> &d) {
        vec<int> iq(N), ct(N); queue<int> Q;
        fill(all(d), inf), d[s] = 0, Q.push(s);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop(), iq[u] = 0;
            each (p, g[u]) {
                int v = p.first, w = p.second;
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    if (!iq[v]) {
                        Q.push(v), iq[v] = 1;
                        if (++ct[v] > N) return false;
                    }
                }
            }
        }
        return true;
    };
    r0p (v, n) if (a[v]) {
        add(v, v + n, -1);
        each (p, R[v]) {
            int u = p.first; add(u, v + n, 8), add(v + n, u, 0);
        }
    }
    vec<int> d(N);
    if (!spfa(n - 1, d)) return cout << -1 << '\n', 0;
    vec<int> A(m, 1);
    r0p (u, n) if (a[u]) each (p, G[u]) A[p.second] = d[p.first] - d[u];
    cout << n << ' ' << m << '\n';
    r0p (i, m) cout << E[i].first + 1 << ' ' << E[i].second + 1 << ' ' << A[i] << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
