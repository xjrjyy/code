/* noip2018s_2a_travel.cpp */
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

const int maxn = 5e5 + 5;
const int inf = ~0u >> 2;

int n, m, s, t, S[maxn], vs[maxn], is[maxn], fl = 1;
vec<int> G[maxn];
vec<int> A;

bool fdc(int u, int fa) {
    vs[S[++*S] = u] = 1;
    each (v, G[u]) if (v != fa) {
        if (vs[v]) return s = v, t = u, true;
        if (fdc(v, u)) return true;
    }
    return vs[u] = 0, --*S, false;
}
vec<int>::iterator jmp_is(const vec<int> &v, vec<int>::iterator x) {
    while (x != v.end() && is[*x]) ++x;
    return x;
}
int nxt(int u, int v, bool f = true) {
    auto x = next(find_if(all(G[u]), [&](int u) { return u == v; }));
    if (f) x = jmp_is(G[u], x);
    return x == G[u].end() ? inf : *x;
}
int gvl(int u, int nx) {
    vs[u] = 1;
    auto x = find_if(all(G[u]), [](int u) { return !vs[u] && is[u]; });
    if (x == G[u].end()) return vs[u] = 0, -1;
    int w = nxt(u, *x); if (w == inf) w = nx;
    int A = (jmp_is(G[u], next(x)) == G[u].end() && w < *x ? *x : gvl(*x, w));
    return vs[u] = 0, A;
}
void dfs2(int u, int ban) {
    A.push_back(u), vs[u] = 1;
    each (v, G[u]) if (!vs[v] && v != ban) dfs2(v, ban);
}
void dfs(int u) {
    A.push_back(u), vs[u] = 1;
    each (v, G[u]) if (!vs[v]) {
        if (is[u] && is[v] && fl) dfs2(v, gvl(v, nxt(u, v, false))), fl = 0;
        else dfs(v);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    r0p (_, m) {
        int u, v; cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    if (m == n) {
        fdc(1, -1), fill(vs + 1, vs + n + 1, 0);
        while (S[*S + 1] != s) is[S[(*S)--]] = 1;
    }
    rep (i, 1, n) sort(all(G[i]));
    dfs(1);
    each (x, A) cout << x << ' ';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
