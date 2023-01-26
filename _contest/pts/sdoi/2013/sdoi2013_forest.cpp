/* sdoi2013_forest.cpp */
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

const int maxn = 8e4 + 5;
const int maxw = 20;

struct DSU {
    int fa[maxn], sz[maxn];
    void init(int n) { rep (i, 1, n) fa[i] = i, sz[i] = 1; }
    int fd(int x) { return fa[x] == x ? x : fa[x] = fd(fa[x]); }
    void mg(int u, int v) { fa[v] = u, sz[u] += sz[v]; }
} dsu;
struct Node {
    Node *ls, *rs; int sz;
    Node(Node *l, Node *r, int s) : ls(l), rs(r), sz(s) {}
    Node() : Node(nullptr, nullptr, 0) {}
} *null = new Node(), _s[maxn * maxw * maxw / 2]; int tt; // nlog^2n
Node *new_nd(Node *l, Node *r, int s) { return &(_s[++tt] = Node(l, r, s)); }
Node *new_nd(int s) { return new_nd(null, null, s); }
void clone(Node *(&u)) { u = new_nd(u->ls, u->rs, u->sz); }
void mdf(Node *(&u), int l, int r, int p) {
    clone(u), u->sz += 1; if (l == r) return;
    int mid = (l + r) / 2;
    if (p <= mid) mdf(u->ls, l, mid, p);
    else mdf(u->rs, mid + 1, r, p);
}
int qry(Node *a, Node *b, Node *c, Node *d, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) / 2, o = a->ls->sz + b->ls->sz - c->ls->sz - d->ls->sz;
    if (k <= o) return qry(a->ls, b->ls, c->ls, d->ls, l, mid, k);
    else return qry(a->rs, b->rs, c->rs, d->rs, mid + 1, r, k - o);
}

int typ, n, m, w, q, a[maxn], A; pair<int, int> b[maxn];
vec<int> G[maxn]; Node *rt[maxn];
int fa[maxw][maxn], dep[maxn];

int LCA(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    per (i, w, 0) if (dep[u] <= dep[fa[i][v]]) v = fa[i][v];
    per (i, w, 0) if (fa[i][u] != fa[i][v]) u = fa[i][u], v = fa[i][v];
    return u == v ? u : fa[0][u];
}
void dfs(int u) {
    dep[u] = dep[fa[0][u]] + 1, mdf(rt[u] = rt[fa[0][u]], 1, n, a[u]);
    each (v, G[u]) if (v != fa[0][u]) fa[0][v] = u, dfs(v);
    rep (i, 1, w) fa[i][u] = fa[i - 1][fa[i - 1][u]];
}
void dfs2(int u) {
    rep (i, 1, w) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    each (v, G[u]) if (v != fa[0][u]) dfs2(v);
}
void Lnk(int u, int v) {
    int U = dsu.fd(u), V = dsu.fd(v);
    if (dsu.sz[U] < dsu.sz[V]) swap(u, v), swap(U, V);
    dsu.mg(U, V), G[u].push_back(v), G[v].push_back(u);
    fa[0][v] = u, dfs(v), dfs2(v);
}
int Qry(int u, int v, int k) {
    int w = LCA(u, v);
    return qry(rt[u], rt[v], rt[w], rt[fa[0][w]], 1, n, k);
}
void prt(Node *u, int l, int r) {
    if (u->sz == 0) return;
    if (l == r) return cerr << l << " ", void();
    int mid = (l + r) / 2;
    prt(u->ls, l, mid), prt(u->rs, mid + 1, r);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> typ >> n >> m >> q, w = ceil(log2(n));
    rt[0] = null->ls = null->rs = null;
    rep (i, 1, n) cin >> a[i], b[i] = {a[i], i};
    sort(b + 1, b + n + 1);
    rep (i, 1, n) a[b[i].second] = i;
    dsu.init(n);
    rep (i, 1, n) dep[i] = 1, mdf(rt[i] = null, 1, n, a[i]);
    rep (i, 1, m) { int u, v; cin >> u >> v; Lnk(u, v); }
    rep (_, 1, q) {
        char o; int u, v, k; cin >> o >> u >> v, u ^= A, v ^= A;
        if (o == 'L') Lnk(u, v);
        if (o == 'Q') cin >> k, k ^= A, cout << (A = b[Qry(u, v, k)].first) << endl;
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
