/* cf_1190_d.cpp */
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

mt19937 rnd(time(0));
struct node { int x, y; };

struct DS {
    struct Node {
        Node *ls, *rs;
        int vl, sz; unsigned rw;
        Node() {}
        Node(Node *l, Node *r, int v, int s) : ls(l), rs(r), vl(v), sz(s), rw(rnd()) {}
    } *rt, *null;
    DS() {
        null = new Node(nullptr, nullptr, 0, 0), null->ls = null->rs = null;
        rt = new Node(null, null, ~0u >> 1, 1);
    }
    void U(Node *u) { u->sz = u->ls->sz + u->rs->sz + 1; }
    void sp(Node *u, int v, Node *&x, Node *&y) {
        if (!u->sz) return x = y = null, void();
        if (u->vl > v) return y = u, sp(u->ls, v, x, y->ls), U(u);
        else return x = u, sp(u->rs, v, x->rs, y), U(u);
    }
    Node *mg(Node *u, Node *v) {
        if (!u->sz || !v->sz) return u->sz ? u : v;
        if (u->rw <= v->rw) return u->rs = mg(u->rs, v), U(u), u;
        else return v->ls = mg(u, v->ls), U(v), v;
    }
    void ins(int v) {
        Node *u = new Node(null, null, v, 1);
        Node *x, *y; sp(rt, v - 1, x, y);
        rt = mg(mg(x, u), y);
    }
    int kth(int v) {
        Node *x, *y; sp(rt, v - 1, x, y);
        int A = x->sz + 1; rt = mg(x, y);
        return A;
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vec<node> a(n); vec<int> b;
    each (x, a) cin >> x.x >> x.y, b.push_back(x.x);
    sort(all(b)), b.erase(unique(all(b)), b.end());
    auto Id = [&](int &x) { x = lower_bound(all(b), x) - b.begin(); };
    each (x, a) Id(x.x);
    int m = int(b.size()); vec<int> c(m); DS ds;
    sort(all(a), [](const node &x, const node &y) {
        return x.y != y.y ? x.y > y.y : x.x < y.x;
    });
    int t = 0; ll A = 0;
    for (int l = 0, r; l < n; l = r + 1) {
        r = l; while (r + 1 < n && a[r + 1].y == a[l].y) ++r;
        rep (i, l, r) if (++c[a[i].x] == 1) ++t, ds.ins(a[i].x);
        A += ll(t) * (t + 1) / 2;
        int u = 0;
        rep (i, l, r) {
            int v = ds.kth(a[i].x) - 1, d = v - u;
            A -= ll(d) * (d + 1) / 2, u = v + 1;
        }
        int d = t - u;
        A -= ll(d) * (d + 1) / 2;
    }
    cout << A;
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
