/* cf_51_f.cpp */
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
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m; cin >> n >> m;
    vec<vec<int>> G(n);
    r0p (_, m) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u);
    }
    vec<int> dfn(n), low(n), S, scn(n); int dtt = 0, k = 0;
    auto form = [&](int u) {
        for (int v = -1; v != u; S.pop_back()) scn[v = S.back()] = k;
        ++k;
    };
    function<void(int, int)> dfs = [&](int u, int fa) {
        dfn[u] = low[u] = ++dtt, S.push_back(u);
        each (v, G[u]) if (v != fa) {
            if (!dfn[v]) {
                dfs(v, u), low[u] = min(low[u], low[v]);
                if (dfn[u] < low[v]) form(v);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (!~fa) form(u);
    };
    r0p (i, n) if (!dfn[i]) dfs(i, -1);
    vec<vec<int>> T(k);
    r0p (u, n) each (v, G[u]) if (scn[u] != scn[v]) T[scn[u]].push_back(scn[v]);
    vec<int> d(k, -1);
    function<int(int, int)> dfs2 = [&](int u, int fa) {
        int A = u;
        each (v, T[u]) if (v != fa) {
            d[v] = d[u] + 1; int B = dfs2(v, u);
            if (d[B] > d[A]) A = B;
        }
        return A;
    };
    int A = 0, B = 0;
    auto solve = [&](int u) {
        if (T[u].empty()) return ++A, void();
        d[u] = 0; int s = dfs2(u, -1);
        d[s] = 0; int t = dfs2(s, -1);
        A += d[t] - 1;
    };
    r0p (i, k) if (!~d[i]) solve(i), ++B;
    A += count_if(all(T), [](const vec<int> &x) { return int(x.size()) == 1; });
    cout << n - A + (B - 1) << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
