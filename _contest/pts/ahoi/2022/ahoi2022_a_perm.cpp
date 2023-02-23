/* ahoi2022_a_perm.cpp */
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

const int mod = 1e9 + 7;
void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}

vec<int> inv, vs, mp, P; vec<vec<pair<int, int>>> pr;
void init(int n) {
    inv.resize(n + 1), inv[1] = 1;
    rep (i, 2, n) inv[i] = ll(mod - mod / i) * inv[mod % i] % mod;
    vs.resize(n + 1), mp.resize(n + 1), pr.resize(n + 1);
    rep (i, 2, n) {
        if (!vs[i]) mp[i] = int(P.size()), P.push_back(i);
        each (p, P) {
            if (i * p > n) break;
            vs[i * p] = 1, mp[i * p] = mp[p];
            if (i % p == 0) break;
        }
    }
    rep (i, 1, n) {
        int x = i;
        while (x > 1) {
            int d = mp[x], v = 1, p = P[d];
            while (x % p == 0) x /= p, v *= p;
            pr[i].push_back({d, v});
        }
    }
}
struct Qmx {
    int a, b, c;
    Qmx() : a(1), b(0), c(0) {}
    void upd(int x) {
        if (x >= a) c = b, b = a, a = x;
        else if (x >= b) c = b, b = x;
        else if (x >= c) c = x;
    }
    void del(int x, ll &A) {
        A = ll(A) * inv[qry()] % mod;
        if (a == x) a = -x;
        else if (b == x) b = -x;
        else if (c == x) c = -x;
        A = ll(A) * qry() % mod;
    }
    void add(int x, ll &A) {
        A = ll(A) * inv[qry()] % mod * max(qry(), x) % mod;
    }
    void clr() {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        if (c < 0) c = -c;
    }
    int qry() { assert(max(max(a, b), c) > 0); return max(max(a, b), c); }
};
struct DS {
    vec<Qmx> f; int A;
    DS() : f(P.size()), A(1) {}
    void add(int x) { each (p, pr[x]) f[p.first].upd(p.second); }
    void init() { r0p (i, int(P.size())) A = ll(A) * f[i].a % mod; }
    void del(int x, ll &A) { each (p, pr[x]) f[p.first].del(p.second, A); }
    void add(int x, ll &A) { each (p, pr[x]) f[p.first].add(p.second, A); }
    void clr(int x) { each (p, pr[x]) f[p.first].clr(); }
    int qry(int x, int y, int z) {
        ll B = A;
        del(x, B), del(y, B), add(z, B);
        clr(x), clr(y); return B;
    }
};

void solve() {
    int n; cin >> n;
    vec<int> a;
    {
        vec<int> p(n); each (x, p) cin >> x, --x;
        vec<int> vs(n);
        function<int(int)> dfs = [&](int u) {
            return vs[u] ? 0 : (vs[u] = 1, 1 + dfs(p[u]));
        };
        r0p (i, n) if (!vs[i]) a.push_back(dfs(i));
    }
    int m = n; n = int(a.size());
    vec<int> s(m + 1), S;
    each (x, a) if (++s[x] == 1) S.push_back(x);
    DS ds; each (x, a) ds.add(x);
    ds.init();
    int A = 0;
    each (x, S) each (y, S)
        norm(A += ll(s[x]) * s[y] % mod * x % mod * y % mod * ds.qry(x, y, x + y) % mod);
    each (x, S) norm(A -= ll(s[x]) * x % mod * x % mod * ds.qry(x, x, x + x) % mod);
    cout << A << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    init(1e6);
    int T; cin >> T;
    while (T--) solve();
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
