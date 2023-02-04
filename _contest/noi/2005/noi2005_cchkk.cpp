/* noi2005_cchkk.cpp */
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

const int maxn = 1e3 + 5;
const int inf = ~0u >> 2;

int n, m, s, t;
vec<int> G[maxn];
int d[maxn][maxn], to[maxn][maxn]; double f[maxn][maxn];

void bfs(int s, int *d) {
    static queue<int> Q;
    fill(d, d + n + 1, inf), d[s] = 0, Q.push(s);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        each (v, G[u]) if (d[v] > d[u] + 1) d[v] = d[u] + 1, Q.push(v);
    }
}

double F(int s, int t) {
    if (d[s][t] == 0) return 0;
    if (d[s][t] <= 2) return 1;
    if (f[s][t] >= 0) return f[s][t];
    int u = to[to[s][t]][t]; double A = 0;
    each (v, G[t]) A += F(u, v);
    return f[s][t] = 1 + (A + F(u, t)) / (G[t].size() + 1);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> s >> t;
    rep (i, 1, m) {
        int u, v; cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    rep (i, 1, n) bfs(i, d[i]), fill(f[i], f[i] + n + 1, -1.0);
    auto cmp = [&](int t, int u, int v) {
        return d[t][u] < d[t][v] || (d[t][u] == d[t][v] && u < v);
    };
    rep (u, 1, n) rep (v, 1, n) each (w, G[u]) if (cmp(v, w, to[u][v])) to[u][v] = w;
    cout << fixed << setprecision(3) << F(s, t) << "\n";
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
