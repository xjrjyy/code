/* cf_911_g.cpp */
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

const int maxn = 2e5 + 5;
const int maxm = 1e2 + 5;
const int maxlgn = 20;
const int maxN = 4 * maxn * maxlgn + 5;

struct node {
    int ls, rs, sz;
} s[maxN]; int pl[maxN], tt;
void init(int n = maxN - 5) { std::iota(pl, pl + n + 1, 0); }
void touch(int &x) { if (!x) x = pl[++tt]; }
void rec(int &x) { if (x) s[pl[tt--] = x] = {0, 0, 0}, x = 0; }
void U(int u) { s[u].sz = s[s[u].ls].sz + s[s[u].rs].sz; }

void ins(int &u, int l, int r, int p) {
    touch(u), ++s[u].sz; if (l == r) return;
    int mid = (l + r) / 2;
    if (p <= mid) ins(s[u].ls, l, mid, p);
    else ins(s[u].rs, mid + 1, r, p);
}
void sp(int &u, int &v, int l, int r, int L, int R) {
    if (L <= l && r <= R) return v = u, u = 0, void();
    int mid = (l + r) / 2; touch(v);
    if (L <= mid) sp(s[u].ls, s[v].ls, l, mid, L, R);
    if (mid + 1 <= R) sp(s[u].rs, s[v].rs, mid + 1, r, L, R);
    if (U(u), !s[u].sz) rec(u);
    if (U(v), !s[v].sz) rec(v);
}
void mg(int &u, int v, int l, int r) {
    if (!u || !v) return u += v, void();
    int mid = (l + r) / 2;
    mg(s[u].ls, s[v].ls, l, mid), mg(s[u].rs, s[v].rs, mid + 1, r);
}

int n, m = 100, q, a[maxn], rt[maxm];

void prt(int u, int l, int r, int t) {
    if (!u) return;
    if (l == r) return a[l] = t, void();
    int mid = (l + r) / 2;
    prt(s[u].ls, l, mid, t), prt(s[u].rs, mid + 1, r, t);
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n, init();
    rep (i, 1, n) std::cin >> a[i], ins(rt[a[i]], 1, n, i);
    std::cin >> q;
    r0p (_, q) {
        int l, r, x, y, t = 0; std::cin >> l >> r >> x >> y;
        sp(rt[x], t, 1, n, l, r), mg(rt[y], t, 1, n);
    }
    rep (i, 1, m) prt(rt[i], 1, n, i);
    rep (i, 1, n) std::cout << a[i] << ' ';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
