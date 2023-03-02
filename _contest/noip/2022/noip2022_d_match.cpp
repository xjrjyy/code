/* noip2022_d_match.cpp */
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

struct Data {
    ull sx, sy, sxy, s, len;
    Data(ull sx_, ull sy_, ull sxy_, ull s_, ull len_)
        : sx(sx_), sy(sy_), sxy(sxy_), s(s_), len(len_) {}
    Data() : Data(0, 0, 0, 0, 0) {}
};

struct Oper {
    ull a, b, c, d, e, f, g;
    Oper(ull a_, ull b_, ull c_, ull d_, ull e_, ull f_, ull g_)
        : a(a_), b(b_), c(c_), d(d_), e(e_), f(f_), g(g_) {}
    Oper() : Oper(0, 0, 0, 0, 0, 0, 0) {}
    operator bool() const { return a || b || c || d || e || f || g; }
    static Oper MdfA(ull x) { return Oper(x, 0, 0, 0, 0, 0, 0); }
    static Oper MdfB(ull x) { return Oper(0, x, 0, 0, 0, 0, 0); }
    static Oper AddS() { return Oper(0, 0, 0, 0, 0, 0, 1); }
};

Data operator+(const Data &x, const Data &y) {
    return Data(x.sx + y.sx, x.sy + y.sy, x.sxy + y.sxy, x.s + y.s, x.len + y.len);
}

Oper operator*(const Oper &x, const Oper &y) {
    return Oper(
        x.a + y.a,
        x.b + y.b,
        x.c + y.c + x.a * y.b + x.b * y.a,
        x.d + y.d + x.a * y.e + x.b * y.f + x.c * y.g,
        x.e + y.e + x.b * y.g,
        x.f + y.f + x.a * y.g,
        x.g + y.g
    );
}

Data operator*(const Data &x, const Oper &y) {
    return Data(
        x.sx + x.len * y.a,
        x.sy + x.len * y.b,
        x.sxy + x.sx * y.b + x.sy * y.a + x.len * y.c,
        x.s + x.sx * y.e + x.sy * y.f + x.sxy * y.g + x.len * y.d,
        x.len
    );
}

const int maxn = 2.5e5 + 5;
const int maxq = 2.5e5 + 5;
const ull inf = ~0ull >> 2;

#define ls (u << 1)
#define rs (ls | 1)
struct SegTree {
    Data s[maxn << 2]; Oper t[maxn << 2];
    void U(int u) { s[u] = s[ls] + s[rs]; }
    void S(int u, const Oper &x) { s[u] = s[u] * x, t[u] = t[u] * x; }
    void D(int u) { if (t[u]) S(ls, t[u]), S(rs, t[u]), t[u] = Oper(); }
    void bld(int u, int l, int r) {
        s[u].len = r - l + 1; if (l == r) return;
        int mid = (l + r) / 2;
        bld(ls, l, mid), bld(rs, mid + 1, r);
    }
    int L, R; Oper x;
    void mdf(int u, int l, int r) {
        if (L <= l && r <= R) return S(u, x);
        int mid = (l + r) / 2; D(u);
        if (L <= mid) mdf(ls, l, mid);
        if (mid + 1 <= R) mdf(rs, mid + 1, r);
        U(u);
    }
    Data qry(int u, int l, int r) {
        if (L <= l && r <= R) return s[u];
        int mid = (l + r) / 2; D(u);
        if (!(mid + 1 <= R)) return qry(ls, l, mid);
        if (!(L <= mid)) return qry(rs, mid + 1, r);
        return qry(ls, l, mid) + qry(rs, mid + 1, r);
    }
    void arg(int L_, int R_, const Oper &x_ = Oper()) {
        L = L_, R = R_, x = x_;
    }
} sgt;

struct opt { int l, r, i; };

int typ, n, q; ull a[maxn], b[maxn], A[maxq];
opt o[maxq]; vec<int> Q[maxn];
int S[maxn], T[maxn];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> typ >> n;
    rep (i, 1, n) cin >> a[i];
    rep (i, 1, n) cin >> b[i];
    cin >> q;
    rep (i, 1, q) cin >> o[i].l >> o[i].r, Q[o[i].r].push_back(i);
    sgt.bld(1, 1, n), a[S[++*S] = 0] = b[T[++*T] = 0] = inf;
    rep (i, 1, n) {
        while (a[S[*S]] <= a[i]) {
            int L = S[*S - 1] + 1, R = S[*S]; --*S;
            sgt.arg(L, R, Oper::MdfA(a[i] - a[R])), sgt.mdf(1, 1, n);
        }
        while (b[T[*T]] <= b[i]) {
            int L = T[*T - 1] + 1, R = T[*T]; --*T;
            sgt.arg(L, R, Oper::MdfB(b[i] - b[R])), sgt.mdf(1, 1, n);
        }
        S[++*S] = T[++*T] = i;
        sgt.arg(i, i, Oper::MdfA(a[i])), sgt.mdf(1, 1, n);
        sgt.arg(i, i, Oper::MdfB(b[i])), sgt.mdf(1, 1, n);
        sgt.arg(1, i, Oper::AddS()), sgt.mdf(1, 1, n);
        each (j, Q[i]) sgt.arg(o[j].l, i), A[j] = sgt.qry(1, 1, n).s;
    }
    rep (i, 1, q) cout << A[i] << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
