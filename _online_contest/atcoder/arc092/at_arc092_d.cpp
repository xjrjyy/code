/* at_arc092_d.cpp */
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

const int maxn = 1e3 + 5;
const int maxm = 2e5 + 5;

int n, m, id[maxn][maxn], fr[maxm], to[maxm], A[maxm];
std::bitset<maxn> G[maxn], s, t;

int dfn[maxn], low[maxn], vs[maxn], S[maxn], T, scn[maxn], dtt, sct;
void tarjan(int u) {
    dfn[u] = low[u] = ++dtt, vs[S[++T] = u] = 1;
    r0p (v, n) if (G[u][v]) {
        if (!dfn[v]) tarjan(v), low[u] = std::min(low[u], low[v]);
        else if (vs[v]) low[u] = std::min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int v; ++sct;
        do scn[v = S[T--]] = sct, vs[v] = 0; while (v != u);
    }
}

std::queue<int> Q;
void bfs(int o) {
    s[o] = 0, Q.push(o);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop(), t = G[u] & s;
        for (int v = t._Find_first(); v < n; v = t._Find_next(v)) s[v] = 0, Q.push(v);
    }
}
void sol(int u) {
    s.set(), s[u] = 0;
    r0p (v, n) if (G[u][v]) {
        if (!s[v]) A[id[u][v]] = 1;
        else bfs(v);
    }
    s.set(), s[u] = 0;
    p0r (v, n) if (G[u][v]) {
        if (!s[v]) A[id[u][v]] = 1;
        else bfs(v);
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> m;
    r0p (i, m) {
        int u, v; std::cin >> u >> v, --u, --v;
        G[u][v] = 1, id[u][v] = i, fr[i] = u, to[i] = v;
    }
    r0p (u, n) if (!dfn[u]) tarjan(u);
    r0p (u, n) sol(u);
    r0p (i, m) A[i] ^= (scn[fr[i]] == scn[to[i]]);
    r0p (i, m) std::cout << (A[i] ? "diff" : "same") << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
