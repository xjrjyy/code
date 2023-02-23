/* haoi2015_str.cpp */
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

const int maxn = 5e2 + 5;
const int maxm = 5;
const int mod = 998244353;
void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}

int m = maxm;
struct Vec {
    int a[maxm];
    Vec() { r0p (i, m) a[i] = 0; }
    int &operator[](std::size_t p) { return a[p]; }
    int operator[](std::size_t p) const { return a[p]; }
};
struct Mat {
    int a[maxm][maxm];
    Mat() { r0p (i, m) r0p (j, m) a[i][j] = 0; }
    static Mat I() { Mat a; r0p (i, m) { a[i][i] = 1; } return a; }
    int *operator[](std::size_t p) { return a[p]; }
    const int *operator[](std::size_t p) const { return a[p]; }
    friend Mat &operator+=(Mat &x, const Mat &y) {
        r0p (i, m) r0p (j, m) norm(x[i][j] += y[i][j]);
        return x;
    }
    friend Mat operator*(const Mat &x, const Mat &y) {
        Mat z; r0p (i, m) r0p (k, m) r0p (j, m) norm(z[i][j] += 1ll * x[i][k] * y[k][j] % mod);
        return z;
    }
    friend Vec operator*(const Vec &x, const Mat &y) {
        Vec z; r0p (k, m) r0p (j, m) norm(z[j] += 1ll * x[k] * y[k][j] % mod);
        return z;
    }
    friend ostream &operator<<(ostream &out, const Mat &x) {
        r0p (i, m) r0p (j, m) out << x[i][j] << " \n"[j == repj];
        return out;
    }
};

int n; char s[maxn];
Mat T[maxn][10], t;
Mat f[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> (s + 1) >> m, n = strlen(s + 1);
    rep (i, 0, n) T[i][0] = Mat::I();
    r0p (i, m) T[1][1][i + 1][i] = T[1][1][i][m - 1] = 1;
    rep (i, 1, n) {
        rep (j, 2, 9) T[i][j] = T[i][j - 1] * T[i][1];
        T[i + 1][1] = T[i][9] * T[i][1];
    }
    f[0] = Mat::I();
    rep (i, 1, n) {
        t = Mat::I();
        p0r (j, i) {
            if (s[j + 1] - '0') t = t * T[i - j][s[j + 1] - '0'];
            f[i] += f[j] * t;
        }
    }
    cout << f[n][m - 1][m - 1];
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
