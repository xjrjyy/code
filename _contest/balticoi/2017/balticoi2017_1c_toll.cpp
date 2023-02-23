/* balticoi2017_1c_toll.cpp */
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

const int maxn = 5e4 + 5;
const int maxN = 5;
const int inf = ~0u >> 2;
int N = 5;
struct Vec {
    int a[maxN];
    int &operator[](std::size_t p) { return a[p]; }
    const int &operator[](std::size_t p) const { return a[p]; }
    Vec() { r0p (i, N) a[i] = inf; }
};
struct Mat {
    int a[maxN][maxN];
    Mat() { r0p (i, N) r0p (j, N) a[i][j] = inf; }
    int *operator[](std::size_t p) { return a[p]; }
    const int *operator[](std::size_t p) const { return a[p]; }
    static Mat I() { Mat a; r0p (i, N) { a[i][i] = 0; } return a; }
    friend Mat operator*(const Mat &x, const Mat &y) {
        Mat z; r0p (i, N) r0p (k, N) r0p (j, N) z[i][j] = min(z[i][j], x[i][k] + y[k][j]);
        return z;
    }
    friend Vec operator*(const Vec &x, const Mat &y) {
        Vec z; r0p (k, N) r0p (j, N) z[j] = min(z[j], x[k] + y[k][j]);
        return z;
    }
};

Mat f[maxn];
#define ls (u << 1)
#define rs (ls | 1)
struct SegTree {
    Mat s[maxn << 2];
    void U(int u) { s[u] = s[ls] * s[rs]; }
    void bld(int u, int l, int r) {
        if (l == r) return s[u] = f[l], void();
        int mid = (l + r) / 2;
        bld(ls, l, mid), bld(rs, mid + 1, r), U(u);
    }
    void qry(int u, int l, int r, int L, int R, Vec &x) {
        if (L <= l && r <= R) return x = x * s[u], void();
        int mid = (l + r) / 2;
        if (L <= mid) qry(ls, l, mid, L, R, x);
        if (mid + 1 <= R) qry(rs, mid + 1, r, L, R, x);
    }
} sgt;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, q; cin >> N >> n >> m >> q;
    r0p (_, m) {
        int u, v, w; cin >> u >> v >> w;
        f[u / N][u % N][v % N] = w;
    }
    sgt.bld(1, 0, (n - 1) / N);
    r0p (_, q) {
        int u, v; cin >> u >> v;
        if (u / N == v / N) { cout << -1 << '\n'; continue; }
        Vec t; t[u % N] = 0, sgt.qry(1, 0, (n - 1) / N, u / N, v / N - 1, t);
        int A = t[v % N]; if (A == inf) A = -1;
        cout << A << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
