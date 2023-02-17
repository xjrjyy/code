/* luogu_p4366.cpp */
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
    int n, m, c; cin >> n >> m >> c, ++n;
    vec<vec<pair<int, int>>> G(n);
    r0p (_, m) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back({v, w});
    }
    int s, t; cin >> s >> t;
    vec<int> d(n, inf), vs(n);
    priority_queue<pair<int, int>> Q;
    Q.push({-(d[s] = 0), s});
    while (!Q.empty()) {
        int u = Q.top().second; Q.pop(), vs[u] = 0;
        auto relax = [&](int u, int v, int w) {
            if (0 <= v && v < n && d[v] > d[u] + w) {
                d[v] = d[u] + w;
                if (!vs[v]) Q.push({-d[v], v}), vs[v] = 1;
            }
        };
        each (p, G[u]) relax(u, p.first, p.second);
        for (int i = 1; i <= 2 * n; i <<= 1) relax(u, u ^ i, i * c);
    }
    cout << d[t] << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
