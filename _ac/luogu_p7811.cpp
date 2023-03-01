/* luogu_p7811.cpp */
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

const int maxn = 3e5 + 5;
const int maxq = 3e5 + 5;
const int maxV = 1e5 + 5;
const int inf = ~0u >> 2;

template <typename T> void umin(T &x, const T &y) { if (y < x) x = y; }
template <typename T> void umax(T &x, const T &y) { if (x < y) x = y; }

struct opt { int l, r, k; };

int n, q, V, a[maxn], A[maxq];
opt o[maxq]; vec<int> Q[maxV]; int QL[maxV], QR[maxV], QC[maxV], vs[maxq];

int bm(const opt &t) {
    int A = inf;
    rep (i, t.l, t.r) A = min(A, a[i] % t.k);
    return A;
}

namespace Solve1 {
const int maxN = 5e2 + 5;
const int maxm = 3e3 + 5;
const int maxlgm = 13;
const int N = 450;
int m, B[maxn], L[maxm], R[maxm];
int s[maxn], t[maxm];
int bqry(int l, int r) { return *min_element(s + l, s + r + 1); }
int aqry(int l, int r) { return l > r ? inf : *min_element(t + l, t + r + 1); }
int qry(int l, int r) {
    if (B[l] == B[r]) return bqry(l, r);
    return min(min(bqry(l, R[B[l]]), bqry(L[B[r]], r)), aqry(B[l] + 1, B[r] - 1));
}
int C[maxV];
void solve() {
    rep (i, 1, n) B[i] = (i - 1) / N + 1;
    m = B[n];
    rep (i, 1, m) L[i] = (i - 1) * N + 1, R[i] = min(n, i * N);
    rep (k, 1, V) if (!Q[k].empty()) {
        double u = n, v = 16.0 * V * QC[k] / k;
        if (u > v) continue;
        vs[k] = 1;
        r0p (i, k) C[i] = i;
        rep (i, k, V) C[i] = C[i - k];
        rep (i, 1, m) t[i] = inf;
        rep (i, QL[k], QR[k]) s[i] = C[a[i]], umin(t[B[i]], s[i]);
        each (i, Q[k]) umin(A[i], qry(o[i].l, o[i].r));
    }
}
}

const int maxN = 2e3 + 5;
const int maxm = 1e3 + 5;
const int maxlgm = 13;

const int N = 1200;
int m, B[maxn], L[maxm], R[maxm];

namespace Solve2 {
struct RMQ {
    int m, t[maxlgm][maxm], lg[maxm];
    void init(int n) {
        m = n, lg[0] = lg[1] = 0; rep (i, 2, m) lg[i] = lg[i >> 1] + 1;
        rep (i, 0, lg[m]) rep (j, 1, m - (1 << i) + 1) t[i][j] = inf;
    }
    void mdf(int p, int x) {
        rep (i, 0, lg[m]) rep (j, max(1, p - (1 << i) + 1), min(m - (1 << i) + 1, p))
            t[i][j] = x;
    }
    int range(int l, int r) {
        if (l > r) return inf;
        int k = lg[r - l + 1];
        return min(t[k][l], t[k][r - (1 << k) + 1]);
    }
} rmq;
vec<int> b[maxV]; int s[maxn], t[maxn], c[maxm];
void mdf(int p, int d) {
    rep (i, L[B[p]], p) s[i] = d;
    rep (i, p, R[B[p]]) t[i] = d;
    c[B[p]] = d, rmq.mdf(B[p], d);
}
int qry(int l, int r) {
    return min(min(s[l], t[r]), rmq.range(B[l] + 1, B[r] - 1));
}
void upd(int k, int d) {
    if (vs[k]) return;
    each (i, Q[k]) umin(A[i], qry(o[i].l, o[i].r) - d);
}
void solve() {
    rmq.init(m);
    rep (i, 1, n) b[a[i]].push_back(i), s[i] = t[i] = inf;
    rep (i, 1, m) c[i] = inf;
    per (i, V, 1) {
        each (p, b[i]) mdf(p, i);
        for (int j = 1; j * j <= i; ++j) if (i % j == 0) {
            upd(j, i); if (j * j != i) upd(i / j, i);
        }
    }
    rep (i, 1, V) upd(i, 0);
}
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    rep (i, 1, n) cin >> a[i], V = max(V, a[i]);
    rep (i, 1, q) cin >> o[i].l >> o[i].r >> o[i].k, V = max(V, o[i].k);
    rep (i, 1, V) QL[i] = inf;
    rep (i, 1, q) umin(QL[o[i].k], o[i].l), umax(QR[o[i].k], o[i].r), ++QC[o[i].k];

    rep (i, 1, n) B[i] = (i - 1) / N + 1;
    m = B[n];
    rep (i, 1, m) L[i] = (i - 1) * N + 1, R[i] = min(n, i * N);

    rep (i, 1, q) {
        if (B[o[i].l] == B[o[i].r]) A[i] = bm(o[i]);
        else Q[o[i].k].push_back(i), A[i] = inf;
    }
    Solve1::solve();
    Solve2::solve();

    rep (i, 1, q) cout << A[i] << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
