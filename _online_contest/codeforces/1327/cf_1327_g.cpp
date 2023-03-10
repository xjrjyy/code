/* cf_1327_g.cpp */
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

template <typename T> T &umx(T &x, const T &y) { return x < y ? x = y : x; }

const int maxm = 1e3 + 5;
struct ACAM {
    int t[maxm][14], a[maxm], fa[maxm], m;
    int touch(int &x) { return !x ? x = ++m : x; }
    void ins(const std::string &s, int x) {
        int u = 0;
        each (c, s) u = touch(t[u][c - 'a']);
        a[u] += x;
    }
    vec<int> G[maxm];
    void dfs(int u) {
        each (v, G[u]) a[v] += a[u], dfs(v);
    }
    void bld() {
        std::queue<int> Q;
        r0p (i, 14) if (t[0][i]) Q.push(t[0][i]);
        while (!Q.empty()) {
            int u = Q.front(), v; Q.pop();
            r0p (i, 14)
                if (v = t[u][i]) fa[v] = t[fa[u]][i], Q.push(v);
                else t[u][i] = t[fa[u]][i];
        }
        rep (i, 1, m) G[fa[i]].push_back(i);
        dfs(0), a[0] = 0;
    }
} ac;

const int maxU = (1 << 14) + 5;
const ll inf = ~0ull >> 2;

int n, m, U; std::string s;
ll _f[2][maxm][maxU], A = -inf; auto f = _f[0], g = _f[1];

void clr() { rep (i, 0, m) std::fill(f[i], f[i] + U, -inf); }

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> m, U = 1 << 14;
    r0p (_, m) { int x; std::cin >> s >> x; ac.ins(s, x); }
    ac.bld();
    std::cin >> s, n = int(s.size()), m = ac.m;
    clr(), f[0][0] = 0;
    for (int l = 1, r; l <= n; l = r) {
        for (r = l; r <= n && s[r - 1] != '?'; ++r);
        std::swap(f, g), clr();
        if (l == r) {
            rep (u, 0, m) r0p (S, U) if (g[u][S] > -inf) r0p (i, 14) if (~(S >> i) & 1)
                umx(f[ac.t[u][i]][S | (1 << i)], g[u][S] + ac.a[ac.t[u][i]]);
            ++r; continue;
        }
        rep (u, 0, m) {
            int v = u; ll t = 0;
            rep (i, l, r - 1) v = ac.t[v][s[i - 1] - 'a'], t += ac.a[v];
            r0p (S, U) if (g[u][S] > -inf) umx(f[v][S], g[u][S] + t);
        }
    }
    rep (u, 0, m) r0p (S, U) A = std::max(A, f[u][S]);
    std::cout << A << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
