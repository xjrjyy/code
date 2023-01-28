/* pkuwc2018_random.cpp 随机游走 */
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

const int maxn = 20;
const int maxm = (1 << 18) + 5;
const int mod = 998244353;

void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}
int qpow(int a, int b) {
    int c = 1;
    for (; b; b >>= 1, a = ll(a) * a % mod) if (b & 1) c = ll(c) * a % mod;
    return c;
}
int inv(int x) { return qpow(x, mod - 2); }

int n, m, q, s, d[maxn], a[maxn], b[maxn], f[maxn][maxm], g[maxm];
vec<int> G[maxn];

void dfs(int u, int fa, int S) {
    a[u] = b[u] = 0; int A = 0, B = 0;
    if ((S >> u) & 1) return;
    each (v, G[u]) if (v != fa) dfs(v, u, S), norm(A += a[v]), norm(B += b[v]);
    norm(a[u] = d[u] - A), a[u] = inv(a[u]), b[u] = ll(a[u]) * (B + d[u]) % mod;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> q >> s, --s, m = 1 << n;
    rep (i, 1, n - 1) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u), ++d[u], ++d[v];
    }
    if (n == 1) {
        rep (_, 1, q) cout << 0 << '\n';
        return 0;
    }
    rep (S, 1, m - 1) dfs(s, -1, S), norm(g[S] = b[s] * (__builtin_popcount(S) & 1 ? 1 : -1));
    for (int l = 1; l < m; l <<= 1) for (int p = 0; p < m; p += 2 * l)
        for (int i = p; i < p + l; ++i) norm(g[i + l] += g[i]);
    rep (_, 1, q) {
        int k, S = 0; cin >> k;
        rep (_, 1, k) { int u; cin >> u, --u; S |= (1 << u); }
        cout << g[S] << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
