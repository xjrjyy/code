/* cf_1207_g.cpp */
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

template <typename T> struct BIT {
    int n; vec<T> t;
    BIT(int n_) : n(n_), t(n + 1) {}
    void add(int p, const T &x) { for (assert(p); p <= n; p += p & -p) t[p] += x; }
    T qry(int p) { T x = T(); for (; p; p -= p & -p) { x += t[p]; } return x; }
    T range(int l, int r) { return qry(r) - qry(l - 1); }
};

const int maxn = 4e5 + 5;
int t[maxn][26], fa[maxn], tt;
int ins(const std::string &s) {
    int u = 0;
    each (x, s) {
        if (!t[u][x - 'a']) t[u][x - 'a'] = ++tt;
        u = t[u][x - 'a'];
    }
    return u;
}
vec<int> G[maxn]; int dfn[maxn], ed[maxn], dtt;
void dfs(int u) {
    dfn[u] = ed[u] = ++dtt;
    each (v, G[u]) dfs(v), ed[u] = ed[v];
}
BIT<int> ds(0);
void bld() {
    static std::queue<int> Q;
    r0p (i, 26) if (t[0][i]) Q.push(t[0][i]);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        r0p (i, 26) {
            if (t[u][i]) fa[t[u][i]] = t[fa[u]][i], Q.push(t[u][i]);
            else t[u][i] = t[fa[u]][i];
        }
    }
    rep (i, 1, tt) G[fa[i]].push_back(i);
    dfs(0), ds = BIT<int>(dtt);
}

int n, q, a[maxn], b[maxn], pos[maxn], A[maxn]; std::string s;
vec<int> g[maxn]; vec<int> Q[maxn]; int o;

void Dfs(int u) {
    int oo = o;
    if (u) {
        o = t[o][a[u]], ds.add(dfn[o], 1);
        each (x, Q[u]) A[x] = ds.range(dfn[pos[x]], ed[pos[x]]);
    }
    each (v, g[u]) Dfs(v);
    if (u) ds.add(dfn[o], -1), o = oo;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n;
    rep (i, 1, n) {
        int o, x = 0; char c; std::cin >> o;
        if (o == 2) std::cin >> x;
        std::cin >> c, g[x].push_back(i), a[i] = c - 'a';
    }
    std::cin >> q;
    rep (i, 1, q) {
        int x; std::cin >> x >> s;
        Q[x].push_back(i), pos[i] = ins(s);
    }
    bld();
    Dfs(0);
    rep (i, 1, q) std::cout << A[i] << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
