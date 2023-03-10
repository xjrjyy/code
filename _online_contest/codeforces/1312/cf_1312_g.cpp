/* cf_1312_g.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = (l), rep##i = (r); i <= rep##i; ++i)
#define per(i, r, l) for (int i = (r), per##i = (l); i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : (s))
#define all(s) (s).begin(), (s).end()
#define dbg(x) (std::cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << std::endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>;

const int maxn = 1e6 + 5;
const int inf = ~0u >> 2;

int n, m, a[maxn], b[maxn], pos[maxn], t[maxn][26], tt, Q[maxn], f[maxn];
int touch(int u, int c) {
    if (!t[u][c]) t[u][c] = ++tt;
    return t[u][c];
}

void dfs(int u) {
    int v; b[u] = a[u];
    r0p (i, 26) if (v = t[u][i]) dfs(v), b[u] += b[v];
}
void dfs2(int u, int F) {
    int v, s = a[u]; F = std::min(F, f[u]);
    r0p (i, 26) if (v = t[u][i]) {
        f[v] = f[u] + 1;
        if (a[v]) f[v] = std::min(f[v], F + s + 1);
        dfs2(v, F + s), s += b[v];
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n;
    rep (i, 1, n) {
        int x; char c; std::cin >> x >> c;
        pos[i] = touch(pos[x], c - 'a');
    }
    std::cin >> m;
    rep (i, 1, m) std::cin >> Q[i], ++a[pos[Q[i]]];
    dfs(0), dfs2(0, 0);
    rep (i, 1, m) std::cout << f[pos[Q[i]]] << ' ';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
