/* cf_750_e.cpp */
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

const int inf = ~0u >> 2;
const int maxn = 2e5 + 5;
struct Vec {
    int a[5];
    int &operator[](std::size_t p) { return a[p]; }
    const int &operator[](std::size_t p) const { return a[p]; }
    Vec() { r0p (i, 5) a[i] = inf; }
};
struct Mat {
    int a[5][5];
    Mat() { r0p (i, 5) r0p (j, 5) a[i][j] = inf; }
    int *operator[](std::size_t p) { return a[p]; }
    const int *operator[](std::size_t p) const { return a[p]; }
    static Mat I() { Mat a; r0p (i, 5) { a[i][i] = 0; } return a; }
    friend Mat operator*(const Mat &x, const Mat &y) {
        Mat z; r0p (i, 5) r0p (k, 5) r0p (j, 5) z[i][j] = min(z[i][j], x[i][k] + y[k][j]);
        return z;
    }
    friend Vec operator*(const Vec &x, const Mat &y) {
        Vec z; r0p (k, 5) r0p (j, 5) z[j] = min(z[j], x[k] + y[k][j]);
        return z;
    }
};

#define ls (u << 1)
#define rs (ls | 1)
Mat f[maxn];
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

int n, q; string s;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> q >> s;
    rep (i, 1, n) {
        char c = s[i - 1]; Mat &F = f[i]; F = Mat::I();
        if (c == '2') F[0][0] = 1, F[0][1] = 0;
        if (c == '0') F[1][1] = 1, F[1][2] = 0;
        if (c == '1') F[2][2] = 1, F[2][3] = 0;
        if (c == '6') F[3][3] = 1, F[4][4] = 1;
        if (c == '7') F[3][3] = 1, F[3][4] = 0;
    }
    sgt.bld(1, 1, n);
    r0p (_, q) {
        int l, r; cin >> l >> r;
        Vec t; t[0] = 0, sgt.qry(1, 1, n, l, r, t);
        int A = t[4]; if (A == inf) A = -1;
        cout << A << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
