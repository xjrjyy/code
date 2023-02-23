/* uoj_p218.cpp */
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
const int maxlgn = 22;
const int maxm = 5e5 + 5;

struct SegTree {
    int s[maxn << 2], t[maxn << 2], l[maxn << 2], r[maxn << 2];
    void S(int u, int x) { s[u] = (r[u] - l[u] + 1) * (t[u] = x); }
    void U(int u) { s[u] = s[u << 1] + s[u << 1 | 1]; }
    void D(int u) { if (t[u]) S(u << 1, t[u]), S(u << 1 | 1, t[u]), t[u] = 0; }
    void bld(int u, int L, int R) {
        l[u] = L, r[u] = R; if (L == R) return;
        int M = (L + R) / 2;
        bld(u << 1, L, M), bld(u << 1 | 1, M + 1, R);
    }
    void mdf(int u, int L, int R, int x) {
        if (L <= l[u] && r[u] <= R) return S(u, x);
        int mid = (l[u] + r[u]) / 2; D(u);
        if (L <= mid) mdf(u << 1, L, R, x);
        if (mid + 1 <= R) mdf(u << 1 | 1, L, R, x);
        U(u);
    }
    int qry(int u, int L, int R) {
        if (L <= l[u] && r[u] <= R) return s[u];
        int mid = (l[u] + r[u]) / 2, A = 0; D(u);
        if (L <= mid) A += qry(u << 1, L, R);
        if (mid + 1 <= R) A += qry(u << 1 | 1, L, R);
        return A;
    }
} sgt;

struct Node { int ls, rs, vl; } s[4 * maxm * maxlgn];
int rt[maxm], tt;
void mdf(int &u, int v, int l, int r, int L, int R, int x) {
    s[u = ++tt] = s[v];
    if (L <= l && r <= R) return s[u].ls = s[u].rs = u, s[u].vl = x, void();
    int mid = (l + r) / 2;
    if (L <= mid) mdf(s[u].ls, s[v].ls, l, mid, L, R, x);
    if (mid + 1 <= R) mdf(s[u].rs, s[v].rs, mid + 1, r, L, R, x);
}
int qry(int u, int l, int r, int p) {
    if (l == r) return s[u].vl;
    int mid = (l + r) / 2;
    if (p <= mid) return qry(s[u].ls, l, mid, p);
    else return qry(s[u].rs, mid + 1, r, p);
}

int n, m, typ, a[maxm], A;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> typ, sgt.bld(1, 1, n);
    auto rd = [&](int &x) { cin >> x, x = (x + A * typ) % n + 1; };
    rep (i, 1, m) {
        int o, l, r; cin >> o, rd(l), rt[i] = rt[i - 1];
        if (o == 1 || o == 3) rd(r), l > r && (swap(l, r), 0);
        if (o == 1) cout << (A = sgt.qry(1, l, r)) << "\n";
        if (o == 2) {
            int p = qry(rt[i - 1], 1, n, l), q; if (!p) continue;
            mdf(rt[i], rt[i - 1], 1, n, l, l, q = qry(rt[p - 1], 1, n, l));
            sgt.mdf(1, l, l, a[q]);
        }
        if (o == 3) cin >> a[i], mdf(rt[i], rt[i - 1], 1, n, l, r, i), sgt.mdf(1, l, r, a[i]);
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
