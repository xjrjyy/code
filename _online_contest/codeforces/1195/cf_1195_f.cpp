/* cf_1195_f.cpp */
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

const int maxn = 1e5 + 5;
const int maxm = 3e5 + 5;
const int maxq = 1e5 + 5;

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

struct node {
    int x, y;
    node(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
    friend node operator-(const node &x, const node &y) {
        node z(x.x - y.x, x.y - y.y); int w = gcd(std::abs(z.x), std::abs(z.y));
        return z.x /= w, z.y /= w, z;
    }
    friend bool operator<(const node &x, const node &y) {
        return x.x == y.x ? x.y < y.y : x.x < y.x;
    }
};

struct qry { int l, r; };

template <typename T> struct BIT {
    int n; vec<T> t;
    BIT(int n_) : n(n_), t(n + 1) {}
    void add(int p, const T &x) { for (; p <= n; p += p & -p) t[p] += x; }
    T qry(int p) { T x = T(); for (; p; p -= p & -p) { x += t[p]; } return x; }
    T range(int l, int r) { return qry(r) - qry(l - 1); }
};

int n, m, q, a[maxn], b[maxm], c[maxm], tt, A[maxq];
std::map<node, int> M; qry Q[maxq];
vec<int> O[maxm];

int id(const node &t) {
    if (!M.count(t)) M[t] = ++tt;
    return M[t];
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n;
    rep (i, 1, n) {
        std::cin >> a[i];
        node s, t; std::cin >> s.x >> s.y, t = s;
        rep (j, 2, a[i]) {
            node u; std::cin >> u.x >> u.y;
            b[++m] = id(u - t), t = u;
        }
        b[++m] = id(s - t), a[i] += a[i - 1];
    }
    std::cin >> q;
    rep (i, 1, q) {
        std::cin >> Q[i].l >> Q[i].r;
        Q[i].l = a[Q[i].l - 1] + 1, O[Q[i].r = a[Q[i].r]].push_back(i);
    }
    BIT<int> ds(m);
    rep (i, 1, m) {
        if (c[b[i]]) ds.add(c[b[i]], 1);
        c[b[i]] = i;
        each (x, O[i]) A[x] = Q[x].r - Q[x].l + 1 - ds.range(Q[x].l, Q[x].r);
    }
    rep (i, 1, q) std::cout << A[i] << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
