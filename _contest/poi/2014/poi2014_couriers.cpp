/* poi2014_couriers.cpp */
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
const int maxm = 5e5 + 5;

struct Qry { int l, r, i; };
bool in(const Qry &q, int x) { return q.l <= x && x < q.r; }
int n, m, a[maxn], A[maxm], ct[maxn], B[maxn];
vec<int> b[maxn]; Qry Q[maxm];

void upd(const Qry &q, int x) {
    int t = upper_bound(all(b[x]), q.r) - lower_bound(all(b[x]), q.l);
    if (t * 2 > q.r - q.l + 1) A[q.i] = x;
}

void solve(int l, int r, int L, int R) {
    if (L > R) return;
    if (l == r) {
        rep (i, L, R) A[Q[i].i] = a[l];
        return;
    }
    int mid = (l + r) / 2, K = L;
    rep (i, L, R) if (in(Q[i], mid)) swap(Q[i], Q[K++]);
    int M = K;
    rep (i, K, R) if (Q[i].r <= mid) swap(Q[i], Q[M++]);
    int mx = 0;
    auto add = [&](int p) {
        if (++ct[a[p]] > ct[mx]) mx = a[p];
        B[p] = mx;
    };
    per (i, mid, l) add(i);
    per (i, mid, l) --ct[a[i]];
    rep (i, mid + 1, r) add(i);
    rep (i, mid + 1, r) --ct[a[i]];
    rep (i, L, K - 1) upd(Q[i], B[Q[i].l]);
    rep (i, L, K - 1) upd(Q[i], B[Q[i].r]);
    solve(l, mid, K, M - 1), solve(mid + 1, r, M, R);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    rep (i, 1, n) cin >> a[i], b[a[i]].push_back(i);
    rep (i, 1, m) cin >> Q[i].l >> Q[i].r, Q[i].i = i;
    solve(1, n, 1, m);
    rep (i, 1, m) cout << A[i] << "\n";
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
