/* cf_1511_f.cpp */
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

const int maxn = 8 + 5;
const int maxm = 8 * 5 + 5;
const int maxN = 700;

int N;
struct mat {
    Z a[maxN][maxN];
    mat() {}
    void I() { rep (i, 1, N) a[i][i] = 1; }
    Z *operator[](std::size_t p) { return a[p]; }
    const Z *operator[](std::size_t p) const { return a[p]; }
    friend mat operator*(const mat &x, const mat &y) {
        mat z; rep (i, 1, N) rep (k, 1, N) rep (j, 1, N) z[i][j] += x[i][k] * y[k][j];
        return z;
    }
};

int n, m, q, vs[maxm], len[maxm], t[maxm][6], tt;
std::string a[maxn], str[maxm];
std::map<std::string, int> M;
int touch(const std::string &s, bool o = false) {
    if (!M.count(s)) str[M[s] = ++m] = s, len[m] = int(s.size());
    vs[M[s]] |= o;
    return M[s];
}
int fd(std::string p, std::string q) {
    if (p.size() < q.size()) std::swap(p, q);
    if (!M.count(p) || !M.count(q)) return -1;
    return t[M[p]][p.size() - q.size()];
}
int Vs(const std::string &s) { return M.count(s) && vs[M[s]]; }

mat T, A;

void add(int u, int v) { if (~u && ~v && u <= N && v <= N) T[u][v] += 1; }

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> q, touch("");
    rep (i, 1, n) {
        std::cin >> a[i]; int o = int(a[i].size());
        rep (j, 1, o) touch(a[i].substr(0, j), j == o);
    }
    rep (i, 1, m) rep (j, 0, len[i]) {
        t[i][j] = ++tt; if (len[i] < 5) N = tt;
    }
    rep (i, 1, m) rep (j, 0, len[i]) r0p (c, 26) {
        std::string p = str[i] + char(c + 'a'), q = p.substr(j);
        bool x = Vs(p), y = Vs(q);
        add(t[i][j], fd(p, q));
        if (x) add(t[i][j], fd("", q));
        if (y) add(t[i][j], fd(p, ""));
        if (x && y) add(t[i][j], fd("", ""));
    }
    A.I();
    for (; q; q >>= 1, T = T * T) if (q & 1) A = A * T;
    std::cout << A[1][1] << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
