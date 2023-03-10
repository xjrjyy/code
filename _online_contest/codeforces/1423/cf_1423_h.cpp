/* cf_1423_h.cpp */
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

const int maxn = 1e5 + 5;

struct DSU {
    struct opt { int x, y, o; };
    int fa[maxn], dp[maxn], sz[maxn]; vec<opt> S;
    void init(int n) {
        std::fill(sz + 1, sz + n + 1, 1);
        std::iota(fa + 1, fa + n + 1, 1);
        enter();
    }
    int fd(int x) { return x == fa[x] ? x : fd(fa[x]); }
    void mg(int u, int v) {
        if ((u = fd(u)) == (v = fd(v))) return;
        if (dp[u] < dp[v]) std::swap(u, v);
        int o = (dp[u] == dp[v]);
        fa[v] = u, dp[u] += o, sz[u] += sz[v];
        S.push_back({u, v, o});
    }
    int siz(int u) { return sz[fd(u)]; }
    void enter() { S.push_back({-1, -1, -1}); }
    void cancel() {
        for (S.pop_back(); ~S.back().o; S.pop_back()) {
            int u = S.back().x, v = S.back().y, o = S.back().o;
            sz[u] -= sz[v], dp[u] -= o, fa[v] = v;
        }
    }
} dsu;

const int maxq = 5e5 + 5;

struct opt { int x, y; };

int n, m, q, k, pos[maxq], cur[maxq], day[maxq], A[maxq];
opt Q[maxq]; vec<int> O[maxq];

#define ls (u << 1)
#define rs (ls | 1)

struct SegTree {
    vec<int> s[maxq << 2];
    void mdf(int u, int l, int r, int L, int R, int x) {
        if (L <= l && r <= R) return s[u].push_back(x), void();
        int mid = (l + r) / 2;
        if (L <= mid) mdf(ls, l, mid, L, R, x);
        if (mid + 1 <= R) mdf(rs, mid + 1, r, L, R, x);
    }
    void solve(int u, int l, int r) {
        each (x, s[u]) dsu.mg(Q[x].x, Q[x].y);
        dsu.enter();
        if (l == r) {
            if (pos[l]) std::cout << dsu.siz(pos[l]) << '\n';
            return dsu.cancel();
        }
        int mid = (l + r) / 2;
        solve(ls, l, mid), solve(rs, mid + 1, r);
        dsu.cancel();
    }
} sgt;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> q >> k, m = 1, dsu.init(n);
    rep (i, 1, q) {
        int o; std::cin >> o;
        if (o == 1) O[m].push_back(i), cur[i] = m, std::cin >> Q[i].x >> Q[i].y;
        if (o == 2) std::cin >> pos[i];
        if (o == 3) day[++m] = i;
    }
    day[++m] = q;
    rep (i, 1, q) if (Q[i].x) sgt.mdf(1, 1, q, i, day[std::min(cur[i] + k, m)], i);
    sgt.solve(1, 1, q);
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
