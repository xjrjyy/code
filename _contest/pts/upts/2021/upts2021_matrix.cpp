/* upts2021_matrix.cpp */
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

const int maxn = 3e2 + 5;
const int maxN = 2 * maxn;
const int K = 1e6;
const ll inf = ~0ull >> 2;

int n, m, N, a[maxn][maxn], b[maxn][maxn];

vec<pair<int, int>> G[maxN];
queue<int> Q; ll d[maxN]; int vs[maxN], ct[maxN];
bool spfa() {
    rep (i, 0, N) d[i] = inf, vs[i] = ct[i] = 0;
    Q.push(0), d[0] = 0;
    while (!Q.empty()) {
        int u = Q.front(); Q.pop(); vs[u] = 0;
        each (e, G[u]) if (d[e.first] > d[u] + e.second) {
            d[e.first] = d[u] + e.second;
            if (!vs[e.first]) {
                Q.push(e.first), vs[e.first] = 1;
                if (++ct[e.first] > N) return false;
            }
        }
    }
    return true;
}

void solve() {
    cin >> n >> m, N = n + m;
    rep (i, 1, n - 1) rep (j, 1, m - 1) cin >> b[i][j];
    rep (i, 1, n) a[i][m] = 0;
    rep (i, 1, m) a[n][i] = 0;
    per (i, n - 1, 1) per (j, m - 1, 1)
        a[i][j] = b[i][j] - a[i + 1][j] - a[i][j + 1] - a[i + 1][j + 1];
    rep (i, 0, N) G[i].clear();
    rep (i, 1, N) G[0].push_back({i, 0});
    rep (i, 1, n) rep (j, 1, m) {
        int u = i, v = n + j; if ((i + j) & 1) swap(u, v);
        G[u].push_back({v, a[i][j]});
        G[v].push_back({u, K - a[i][j]});
    }
    if (!spfa()) return cout << "NO\n", void();
    cout << "YES\n";
    rep (i, 1, n) rep (j, 1, m) a[i][j] += (d[i] - d[n + j]) * ((i + j) & 1 ? -1 : 1);
    rep (i, 1, n) rep (j, 1, m) cout << a[i][j] << " \n"[j == repj];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T; cin >> T;
    while (T--) solve();
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
