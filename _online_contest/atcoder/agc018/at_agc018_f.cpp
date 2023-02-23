/* at_agc018_f.cpp */
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, p, q; cin >> n;
    struct Tree {
        int n, rt; vec<int> fa; vec<vec<int>> G;
        Tree(int n_) : n(n_), rt(-1), fa(n), G(n) {}
        void in() {
            r0p (u, n) {
                cin >> fa[u];
                if (~fa[u]) G[--fa[u]].push_back(u);
                else rt = u;
            }
        }
        function<void(int &, int)> F;
        int dfs(int u) {
            int x = -1;
            each (v, G[u]) F(x, dfs(v));
            if (~G[u].size() & 1) F(x, u);
            return x;
        }
    } a(n), b(n);
    a.in(), b.in();
    vec<vec<int>> G(n);
    auto add = [&](int &u, int v) {
        if (~u) G[u].push_back(v), G[v].push_back(u), u = -1;
        else u = v;
    };
    a.F = b.F = add;
    a.dfs(a.rt), b.dfs(b.rt);
    vec<int> s(n), t(n);
    r0p (i, n) {
        if ((a.G[i].size() & 1) != (b.G[i].size() & 1)) return cout << "IMPOSSIBLE\n", 0;
        t[i] = (~a.G[i].size() & 1);
    }
    function<void(int)> dfs = [&](int u) {
        each (v, G[u]) if (!s[v]) s[v] = -s[u], dfs(v);
    };
    r0p (i, n) if (t[i] && !s[i]) s[i] = 1, dfs(i);
    cout << "POSSIBLE\n";
    r0p (i, n) cout << s[i] << ' ';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
