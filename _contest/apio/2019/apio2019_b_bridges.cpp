/* apio2019_b_bridges.cpp */
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

struct edge { int u, v, w, i; };
struct opt { int x, y, i; };

struct DSU {
    int n; vec<int> fa, sz, S;
    DSU(int n_) : n(n_), fa(n), sz(n, 1) { iota(all(fa), 0); }
    int fd(int x) const { return x == fa[x] ? x : fd(fa[x]); }
    void mg(int u, int v, bool t) {
        if ((u = fd(u)) == (v = fd(v))) return;
        if (sz[u] < sz[v]) swap(u, v);
        fa[v] = u, sz[u] += sz[v]; if (t) S.push_back(v);
    }
    void clr() {
        while (!S.empty()) {
            int u = S.back(); S.pop_back();
            sz[fa[u]] -= sz[u], fa[u] = u;
        }
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, T; cin >> n >> m, T = sqrt(m * log2(m) / log2(n + 1)), T = max(T, 1);
    vec<edge> E(m);
    r0p (i, m) cin >> E[i].u >> E[i].v >> E[i].w, --E[i].u, --E[i].v, E[i].i = i;
    int q; cin >> q; vec<int> A(q, -1);
    auto solve = [&](vec<opt> &Q, vec<opt> &M) {
        sort(all(Q), [](const opt &x, const opt &y) { return x.y > y.y; });
        sort(all(M), [](const opt &x, const opt &y) { return x.i < y.i; });
        sort(all(E), [](const edge &x, const edge &y) { return x.w > y.w; });
        vec<int> ps(m), vs(m); vec<vec<pair<int, int>>> vl(m);
        r0p (i, m) ps[E[i].i] = i;
        each (x, M) {
            x.x = ps[x.x];
            if (vl[x.x].empty()) vl[x.x].push_back({E[x.x].w, -1});
            vl[x.x].push_back({x.y, x.i});
        }
        int L = 0; DSU dsu(n);
        auto add = [&](const edge &e, bool t) { dsu.mg(e.u, e.v, t); };
        auto qry = [&](int u) { return dsu.sz[dsu.fd(u)]; };
        each (x, Q) {
            while (L < m && E[L].w >= x.y) {
                if (vl[L].empty()) add(E[L], false);
                ++L;
            }
            each (y, M) if (!vs[y.x]) {
                vs[y.x] = 1;
                auto t = find_if(all(vl[y.x]), [&](const pair<int, int> &p) {
                    return p.second > x.i;
                });
                if (t != vl[y.x].begin() && prev(t)->first >= x.y) add(E[y.x], true);
            }
            A[x.i] = qry(x.x);
            dsu.clr(); each (y, M) vs[y.x] = 0;
        }
        r0p (i, m) if (!vl[i].empty()) E[i].w = vl[i].back().first;
        Q.clear(), M.clear();
    };
    vec<opt> Q, M;
    r0p (i, q) {
        int o; opt x; cin >> o >> x.x >> x.y, --x.x, x.i = i;
        (o == 1 ? M : Q).push_back(x);
        if ((i + 1) % T == 0) solve(Q, M);
    }
    if (!Q.empty()) solve(Q, M);
    each (x, A) if (~x) cout << x << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
