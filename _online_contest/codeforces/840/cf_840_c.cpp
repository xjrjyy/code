/* cf_840_c.cpp */
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

const int P = 1e9 + 7;

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

const int maxn = 3e2 + 5;
const int maxm = 4e4 + 5;

vec<int> pri; std::bitset<maxm> vs;
void init(int n) {
    rep (i, 2, n) {
        if (!vs[i]) pri.push_back(i);
        each (p, pri) {
            if (i * p > n) break;
            vs[i * p] = 1; if (i % p == 0) break;
        }
    }
}
void red(int &x) {
    each (p, pri) {
        if (p * p > x) break;
        while (x % (p * p) == 0) x /= p * p;
    }
}

int n, m, a[maxn]; Z fc[maxn], ifc[maxn], f[maxn][maxn], A;
std::map<int, int> M;

void Init(int n) {
    fc[0] = 1; rep (i, 1, n) fc[i] = fc[i - 1] * i;
    ifc[n] = fc[n].inv(); per (i, n, 1) ifc[i - 1] = ifc[i] * i;
}
Z C(int n, int m) { return n < m ? Z() : fc[n] * ifc[m] * ifc[n - m]; }

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n, init(maxm - 5), Init(n);
    rep (i, 1, n) std::cin >> a[i], red(a[i]), M[a[i]] += 1;
    each (p, M) a[++m] = p.second;
    f[0][0] = 1;
    rep (i, 1, m) rep (j, 1, n) rep (k, 1, std::min(j, a[i]))
        f[i][j] += f[i - 1][j - k] * fc[a[i]] * C(a[i] - 1, a[i] - k) * ifc[k];
    rep (i, 1, n) A += f[m][i] * fc[i] * Z((n - i) & 1 ? -1 : 1);
    std::cout << A << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
