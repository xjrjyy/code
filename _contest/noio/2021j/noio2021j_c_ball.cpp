/* noio2021j_c_ball.cpp */
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

const int maxn = 2.5e2 + 5;
const int maxm = 2.5e2 + 5;
const int maxN = 4 * (maxn + maxm);
const int inf = ~0u >> 2;
const int Dx[] = {-1, 1, 0, 0}, Dy[] = {0, 0, -1, 1};

int n, N, m, q, a[maxn][maxn];
int id[maxn][maxn], to[maxn][maxn][4];
pair<int, int> ps[maxN];
int g[maxN][4]; vec<int> G[maxN * maxN];

int Gid(int x, int y, int k) {
    x += Dx[k], y += Dy[k];
    if (!id[x][y]) ps[id[x][y] = ++N] = {x, y};
    return id[x][y];
}
int Id(int x, int y, int k) { return x += Dx[k], y += Dy[k], id[x][y]; }
bool in(int x, int y) { return 1 <= x && x <= n && 1 <= y && y <= n; }
bool is(int x, int y, int t) { return in(x, y) && a[x][y] == t; }
void addg(int u, int v, int k) {
    if (u == v) return;
    g[u][k] = v, g[v][k ^ 1] = u;
}
int gid(int x, int y) { return (x - 1) * N + y; }

int d[maxN * maxN]; queue<int> Q;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> q;
    r0p (_, m) { int x, y; cin >> x >> y, a[x][y] = 1; }
    rep (i, 1, n) a[0][i] = a[i][0] = a[n + 1][i] = a[i][n + 1] = 1;
    rep (i, 0, n + 1) rep (j, 0, n + 1) if (a[i][j]) r0p (k, 4) {
        int x = i, y = j, l = 0;
        while (++l, is(x += Dx[k], y += Dy[k], 0)) to[x][y][k ^ 1] = Gid(i, j, k);
        if (l > 1) addg(Gid(i, j, k), Gid(x, y, k ^ 1), k);
    }
    rep (i, 1, n) rep (j, 1, n) if (id[i][j]) r0p (k, 4) {
        int u = id[i][j], v = to[i][j][k];
        if (u != v) addg(u, v, k);
    }
    assert(N <= 4 * (n + m));
    rep (i, 1, N) rep (j, 1, N) r0p (k, 4) {
        int a = ps[i].first, b = ps[i].second, c = ps[j].first, d = ps[j].second;
        G[gid(to[a][b][k], to[c][d][k])].push_back(gid(i, j));
    }
    fill(d + 1, d + N * N + 1, inf);
    rep (i, 1, N) d[gid(i, i)] = 0, Q.push(gid(i, i));
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        each (v, G[u]) if (d[v] > d[u] + 1) d[v] = d[u] + 1, Q.push(v);
    }
    r0p (_, q) {
        int a, b, c, d, A = ~0u >> 2; cin >> a >> b >> c >> d;
        r0p (k, 4) {
            int u = to[a][b][k], v = to[c][d][k];
            A = min(A, ::d[gid(u, v)] + !(id[a][b] == u && id[c][d] == v));
        }
        if (a == c && b == d) A = 0;
        if (A >= inf) A = -1;
        cout << A << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
