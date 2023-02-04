/* noio2s_c_match.cpp */
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

const int maxn = 5e3 + 5;
const int maxm = maxn / 2;
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

int fac[maxm], ifac[maxm];
void init(int n) {
    rep (i, 0, n) fac[i] = (i ? ll(fac[i - 1]) * i % mod : 1);
    ifac[n] = inv(fac[n]);
    per (i, n, 1) ifac[i - 1] = ll(ifac[i]) * i % mod;
}
int C(int n, int m) { return n < m ? 0 : ll(fac[n]) * ifac[m] % mod * ifac[n - m] % mod; }

int n, a[maxn], b[maxn], f[maxn][maxm], g[maxm], A[maxm], B[maxm]; string str;
vec<int> G[maxn];
int sz[maxn];
int S(int s, int t) { return min(t, s - t); }

void dfs(int u, int fa) {
    sz[u] = 1, b[u] = a[u], f[u][0] = 1;
    each (v, G[u]) if (v != fa) {
        dfs(v, u), fill(g, g + S(sz[u] += sz[v], b[u] += b[v]) + 1, 0);
        rep (i, 0, S(sz[u] - sz[v], b[u] - b[v])) if (f[u][i])
            rep (j, 0, S(sz[v], b[v])) if (f[v][j])
                norm(g[i + j] += ll(f[u][i]) * f[v][j] % mod);
        copy(g, g + S(sz[u], b[u]) + 1, f[u]);
    }
    int t = a[u] ? sz[u] - b[u] : b[u];
    per (i, S(sz[u], b[u]), 1) norm(f[u][i] += ll(f[u][i - 1]) * (t - (i - 1)) % mod);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> str, init(n / 2);
    rep (i, 1, n) a[i] = str[i - 1] - '0';
    rep (i, 1, n - 1) {
        int u, v; cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, -1);
    rep (i, 0, n / 2) B[i] = ll(f[1][i]) * fac[n / 2 - i] % mod;
    rep (j, 0, n / 2) rep (i, 0, j)
        norm(A[i] += ll(B[j]) * C(j, i) % mod * ((j - i) & 1 ? mod - 1 : 1) % mod);
    rep (i, 0, n / 2) cout << A[i] << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
