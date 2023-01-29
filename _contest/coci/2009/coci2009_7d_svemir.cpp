/* coci2009_7d_svemir.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : s)
#define all(s) (s).begin(), (s).end()
#define dbg(x) (cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>; using namespace std;

const int inf = ~0u >> 1;
struct DSU {
    int n; vec<int> fa;
    DSU(int n_) : n(n_), fa(n) { iota(all(fa), 0); }
    int fd(int x) { return x == fa[x] ? x : fa[x] = fd(fa[x]); }
    void mg(int u, int v) { fa[v] = u; }
};
struct Node {
    union {
        struct { int x, y, z; };
        int _[3];
    };
    int i;
};
struct Edge { int u, v, w; };
bool operator<(const Edge &x, const Edge &y) { return x.w < y.w; }

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vec<Node> a(n);
    r0p (i, n) cin >> a[i].x >> a[i].y >> a[i].z, a[i].i = i;
    vec<Edge> G; DSU dsu(n);
    r0p (i, 3) {
        sort(all(a), [&](const Node &x, const Node &y) { return x._[i] < y._[i]; });
        rep (i, 1, n - 1) G.push_back({a[i - 1].i, a[i].i, -1});
    }
    sort(all(a), [](const Node &x, const Node &y) { return x.i < y.i; });
    auto W = [&](int u, int v) {
        int w = inf; r0p (i, 3) w = min(w, std::abs(a[u]._[i] - a[v]._[i]));
        return w;
    };
    each (x, G) x.w = W(x.u, x.v);
    sort(all(G));
    ll A = 0;
    each (e, G) {
        int u = e.u, v = e.v, w = e.w;
        if ((u = dsu.fd(u)) != (v = dsu.fd(v))) dsu.mg(u, v), A += w;
    }
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
