/* tjoi2018_xor.cpp */
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

const int maxn = 1e5 + 5;
const int maxw = 32;

struct Node {
    Node *ch[2]; int ct;
    Node() {}
    Node(Node *ls, Node *rs, int v) { ch[0] = ls, ch[1] = rs, ct = v; }
} *null, _t[4 * maxn * maxw]; int tt;
Node *new_nd(int v) { return &(_t[++tt] = Node(null, null, v)); }

Node *bld(int p, int x) {
    Node *u = new_nd(1);
    if (p < 0) return u;
    u->ch[(x >> p) & 1] = bld(p - 1, x);
    return u;
}
Node *mg(int p, Node *u, Node *v) {
    if (!u->ct || !v->ct) return u->ct ? u : v;
    Node *w = new_nd(u->ct + v->ct);
    if (p < 0) return w;
    rep (i, 0, 1) w->ch[i] = mg(p - 1, u->ch[i], v->ch[i]);
    return w;
}

int n, w = 29, q, a[maxn];
vec<int> G[maxn];
Node *rt[maxn], *rt2[maxn];
int fa[maxn], sz[maxn], hs[maxn], dfn[maxn], top[maxn];

void dfs(int u) {
    sz[u] = 1;
    each (v, G[u]) if (v != fa[u]) {
        fa[v] = u, rt2[v] = mg(w, rt2[u], rt2[v]);
        dfs(v);
        rt[u] = mg(w, rt[u], rt[v]), sz[u] += sz[v];
        if (sz[v] > sz[hs[u]]) hs[u] = v;
    }
}
void dfs2(int u, int tp) {
    dfn[u] = ++*dfn, top[u] = tp;
    if (hs[u]) dfs2(hs[u], tp);
    each (v, G[u]) if (v != fa[u] && v != hs[u]) dfs2(v, v);
}
int LCA(int u, int v) {
    while (top[u] != top[v]) {
        if (dfn[u] < dfn[v]) swap(u, v);
        u = fa[top[u]];
    }
    return dfn[u] < dfn[v] ? u : v;
}
int qry(Node *u, Node *v, int x) {
    per (i, w, 0) {
        int p = ~(x >> i) & 1;
        if (!(u->ch[p]->ct - v->ch[p]->ct)) p = !p;
        u = u->ch[p], v = v->ch[p], x ^= p << i;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> q;
    null = new Node(nullptr, nullptr, 0), null->ch[0] = null->ch[1] = null;
    rt[0] = rt2[0] = null;
    rep (i, 1, n) cin >> a[i], rt[i] = bld(w, a[i]), rt2[i] = bld(w, a[i]);
    rep (i, 1, n - 1) {
        int u, v; cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1), dfs2(1, 1);
    rep (_, 1, q) {
        int o, x, y, z; cin >> o >> x >> y;
        if (o == 1) cout << qry(rt[x], null, y) << "\n";
        if (o == 2) {
            cin >> z; int l = fa[LCA(x, y)];
            cout << max(qry(rt2[x], rt2[l], z), qry(rt2[y], rt2[l], z)) << "\n";
        }
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
