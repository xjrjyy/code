/* cf_464_e.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "R", stdin); freopen(#x".out", "w", stdout);
#define rep(i, L, R) for (int i = (l), rep##i = (r); i <= rep##i; ++i)
#define per(i, R, L) for (int i = (r), per##i = (l); i >= per##i; --i)
#define r0p(i, R) rep (i, 0, (R) - 1)
#define p0r(i, L) per (i, (L) - 1, 0)
#define each(x, s) for (auto &x : (s))
#define all(s) (s).begin(), (s).end()
#define dbg(x) (cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>; using namespace std;

const int maxn = 1.1e5;
const int maxlgn = 19;
const int N = 100100;
const int mod = 1e9 + 7;

int pw[maxn];
void init() {
    pw[0] = 1; rep (i, 1, N) pw[i] = pw[i - 1] * 2 % mod;
}

struct Node {
    Node *ls, *rs; int sz, hs, tg;
    Node() { ls = rs = nullptr, sz = 0, hs = 0, tg = 0; }
    Node(Node *L, Node *R, int s, int v, int t) {
        ls = L, rs = R, sz = s, hs = v, tg = t;
    }
    void U() { sz = ls->sz + rs->sz, hs = (ll(rs->hs) * pw[ls->sz] + ls->hs) % mod; }
} _s[16 * maxn * maxlgn], *null; int tt;
Node *new_nd(Node *l, Node *r, int s, int v, int t) { return &(_s[++tt] = Node(l, r, s, v, t)); }
Node *new_nd(int s, int v) { return new_nd(null, null, s, v, 0); }
void clone(Node *(&u)) { u = new_nd(u->ls, u->rs, u->sz, u->hs, u->tg); }
void S(Node *(&u)) { if (u->sz) clone(u), u->hs = 0, u->tg = 1; }
void D(Node *u) { if (u->tg) S(u->ls), S(u->rs), u->tg = 0; }

Node *bld(int l, int r) {
    Node *u = new_nd(r - l + 1, 0); if (l == r) return u;
    int mid = (l + r) / 2;
    return u->ls = bld(l, mid), u->rs = bld(mid + 1, r), u;
}
bool qry(Node *u, int l, int r, int L, int R) {
    if (L <= l && r <= R) return u->hs == pw[u->sz] - 1;
    int mid = (l + r) / 2; D(u);
    if (!(mid + 1 <= R)) return qry(u->ls, l, mid, L, R);
    if (!(L <= mid)) return qry(u->rs, mid + 1, r, L, R);
    return qry(u->ls, l, mid, L, R) && qry(u->rs, mid + 1, r, L, R);
}
int fd(Node *u, int l, int r, int p) {
    if (l == r) return u->hs ? l : l - 1;
    int mid = (l + r) / 2; D(u);
    if (mid < p || qry(u, l, r, p, mid)) return fd(u->rs, mid + 1, r, p);
    else return fd(u->ls, l, mid, p);
}
void clr(Node *(&u), int l, int r, int L, int R) {
    if (L <= l && r <= R) return S(u);
    int mid = (l + r) / 2; clone(u), D(u);
    if (L <= mid) clr(u->ls, l, mid, L, R);
    if (mid + 1 <= R) clr(u->rs, mid + 1, r, L, R);
    u->U();
}
void asi(Node *(&u), int l, int r, int p) {
    if (l == r) return u = new_nd(1, 1), void();
    int mid = (l + r) / 2; clone(u), D(u);
    if (p <= mid) asi(u->ls, l, mid, p), u->U();
    else asi(u->rs, mid + 1, r, p), u->U();
}
Node *Mdf(Node *u, int p) {
    int q = fd(u, 0, N, p);
    if (p <= q) clr(u, 0, N, p, q);
    return asi(u, 0, N, q + 1), u;
}
bool Cmp(Node *u, Node *v, int l, int r) {
    if (u->sz == 1) return u->hs > v->hs;
    int mid = (l + r) / 2; D(u), D(v);
    if (u->rs->hs != v->rs->hs) return Cmp(u->rs, v->rs, mid + 1, r);
    if (u->ls->hs != v->ls->hs) return Cmp(u->ls, v->ls, l, mid);
    return false;
}

struct Data { Node *rt; };
bool operator<(const Data &x, const Data &y) { return Cmp(x.rt, y.rt, 0, N); }
Data operator+(const Data &x, int y) { return {Mdf(x.rt, y)}; }

int n, m, s, t;
vec<pair<int, int>> G[maxn];

priority_queue<pair<Data, int>> Q;
Data d[maxn]; int vs[maxn], fr[maxn];
void dij() {
    d[s].rt = bld(0, N), fr[s] = -1, Q.push({d[s], s});
    while (!Q.empty()) {
        int u = Q.top().second; Q.pop(), vs[u] = false;
        each (p, G[u]) {
            int v = p.first, x = p.second; Data w = d[u] + x;
            if (!fr[v] || d[v] < w) {
                d[v] = w, fr[v] = u;
                if (!vs[v]) Q.push({d[v], v}), vs[v] = true;
            }
        }
    }
}
vec<int> A;
void prt(int u) {
    if (~fr[u]) prt(fr[u]);
    A.push_back(u);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    init(), null = new Node();
    cin >> n >> m;
    rep (i, 1, m) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back({v, w}), G[v].push_back({u, w});
    }
    cin >> s >> t;
    dij();
    cout << (fr[t] ? d[t].rt->hs : -1) << "\n";
    if (fr[t]) {
        prt(t);
        cout << A.size() << "\n";
        each (u, A) cout << u << " ";
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
