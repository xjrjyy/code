/* shoi2014_charger.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : s)
#define all(s) (s).begin(), (s).end()
#define dbg(x) (cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>; using namespace std;

const int maxn = 5e5 + 5;
const double eps = 1e-7;

int n; double a[maxn], f[maxn], g[maxn], A;
vec<pair<int, double>> G[maxn];

void dfs(int u, int fa) {
    f[u] = 1 - a[u], g[u] = 1;
    each (e, G[u]) {
        int v = e.first; double w = e.second; if (v == fa) continue;
        dfs(v, u), f[u] *= 1 - (1 - f[v]) * w;
    }
}
void dfs2(int u, int fa) {
    each (e, G[u]) {
        int v = e.first; double w = e.second; if (v == fa) continue;
        double t = 1 - (1 - f[v]) * w;
        if (t > eps) g[v] = 1 - (1 - f[u] / t * g[u]) * w;
        dfs2(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    rep (i, 1, n - 1) {
        int u, v; double w; cin >> u >> v >> w, w /= 100;
        G[u].push_back({v, w}), G[v].push_back({u, w});
    }
    rep (i, 1, n) cin >> a[i], a[i] /= 100;
    dfs(1, -1), dfs2(1, -1);
    rep (i, 1, n) A += 1 - f[i] * g[i];
    cout << fixed << setprecision(6) << A << "\n";
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
