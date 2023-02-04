/* noi2020_1a_delicacy.cpp */
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

const int W = 5;
const int maxn = 5e1 + 5;
const int maxN = maxn * W;
const int maxlgq = 32;
const int maxk = 2.5e2 + 5;
const ll inf = ~0u >> 2;

int N;
struct Mat {
    ll a[maxN][maxN];
    Mat(ll x = -inf) { rep (i, 1, N) rep (j, 1, N) a[i][j] = x; }
    const ll *operator[](std::size_t p) const { return a[p]; }
    ll *operator[](std::size_t p) { return a[p]; }
    friend Mat operator*(const Mat &x, const Mat &y) {
        Mat z;
        rep (i, 1, N) rep (k, 1, N) rep (j, 1, N) z[i][j] = max(z[i][j], x[i][k] + y[k][j]);
        return z;
    }
    static Mat I() {
        Mat a;
        rep (i, 1, N) a[i][i] = 0;
        return a;
    }
    void prt() const {
        rep (i, 1, N) rep (j, 1, N) cerr << a[i][j] << " \n"[j == N];
    }
};
struct Vec {
    ll a[maxN];
    Vec(ll x = -inf) { rep (i, 1, N) a[i] = x; }
    const ll &operator[](std::size_t p) const { return a[p]; }
    ll &operator[](std::size_t p) { return a[p]; }
    friend Vec operator*(const Vec &x, const Mat &y) {
        Vec z;
        rep (k, 1, N) rep (j, 1, N) z[j] = max(z[j], x[k] + y[k][j]);
        return z;
    }
};
struct Node { int t, p, x; };
bool operator<(const Node &x, const Node &y) { return x.t < y.t; }

int n, m, q, k, c[maxn];
Mat T[maxlgq]; Vec S;
Node s[maxk];

void qpow(Vec &a, int x) {
    for (int i = 0; x; x >>= 1, ++i) if (x & 1) a = a * T[i];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m >> q >> k, N = n * W, *T = Mat(), S = Vec();
    rep (i, 1, n) cin >> c[i];
    rep (i, 1, m) {
        int u, v, w; cin >> u >> v >> w;
        T[0][u * W][v * W - w + 1] = c[v];
    }
    rep (u, 1, n) rep (i, 1, W - 1) T[0][u * W - i][u * W - i + 1] = 0;
    rep (i, 1, 30) T[i] = T[i - 1] * T[i - 1];
    rep (i, 1, k) cin >> s[i].t >> s[i].p >> s[i].x;
    sort(s + 1, s + k + 1);
    if (s[k].t != q) s[++k] = {q, 1, 0};
    S[W] = c[1];
    rep (i, 1, k) qpow(S, s[i].t - s[i - 1].t), S[s[i].p * W] += s[i].x;
    if (S[W] < 0) S[W] = -1;
    cout << S[W] << "\n";
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
