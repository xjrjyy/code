/* cf_1172_c2.cpp */
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

const int P = 998244353;

int fix(int x) {
    assert(-P <= x && x < 2 * P);
    if (x < 0) x += P;
    if (x >= P) x -= P;
    return x;
}
template <class T> T power(T a, ll b) {
    T c = 1; for (; b; b /= 2, a *= a) if (b & 1) c *= a;
    return c;
}
struct Z {
    int x;
    Z(int x = 0) : x(fix(x)) {}
    Z(ll x) : x(fix(x % P)) {}
    int val() const { return x; }
    Z operator-() const { return Z(fix(P - x)); }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) { return x = 1ll * x * rhs.x % P, *this; }
    Z &operator+=(const Z &rhs) { return x = fix(x + rhs.x), *this; }
    Z &operator-=(const Z &rhs) { return x = fix(x - rhs.x), *this; }
    Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
    friend Z operator*(const Z &lhs, const Z &rhs) { Z res = lhs; return res *= rhs; }
    friend Z operator+(const Z &lhs, const Z &rhs) { Z res = lhs; return res += rhs; }
    friend Z operator-(const Z &lhs, const Z &rhs) { Z res = lhs; return res -= rhs; }
    friend Z operator/(const Z &lhs, const Z &rhs) { Z res = lhs; return res /= rhs; }
    friend std::istream &operator>>(std::istream &in, Z &a) {
        ll v; return in >> v, a = Z(v), in;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};

const int maxn = 2e5 + 5;
const int maxm = 3e3 + 5;

int n, m, a[maxn];
Z w[maxn], S[2], F[2][maxm][maxm], A[maxn];

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> m;
    rep (i, 1, n) std::cin >> a[i];
    rep (i, 1, n) std::cin >> w[i], S[a[i]] += w[i];
    r0p (t, 2) {
        auto f = F[t]; f[0][0] = 1; Z p = Z(t ? 1 : -1), q = Z(!t ? 1 : -1);
        rep (i, 1, m) {
            rep (j, 0, i) {
                Z u = S[t] + j * p, v = S[!t] + (i - j) * q, w = u + v;
                if (j > 0 && (w - p).val()) f[i][j] += f[i - 1][j - 1] * Z(u - p) / (w - p);
                if (j < i && (w - q).val()) f[i][j] += f[i - 1][j] * Z(v - q) / (w - q);
            }
        }
        Z o = S[t];
        rep (i, 0, m) o += f[m][i] * i * p;
        if (S[t].val()) o /= S[t];
        rep (i, 1, n) if (a[i] == t) A[i] = o * w[i];
    }
    rep (i, 1, n) std::cout << A[i] << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
