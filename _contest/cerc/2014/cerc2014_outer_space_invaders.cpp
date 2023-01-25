/* cerc2014_outer_space_invaders.cpp */
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

const int inf = ~0u >> 2;
struct node { int l, r, d; };

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vec<node> s(n); vec<int> a{-1};
        each (x, s) cin >> x.l >> x.r >> x.d;
        each (x, s) a.push_back(x.l), a.push_back(x.r);
        sort(all(a)), a.erase(unique(all(a)), a.end());
        int m = int(a.size());
        auto Id = [&](int &x) { x = lower_bound(all(a), x) - a.begin(); };
        each (x, s) Id(x.l), Id(x.r);
        vec<vec<int>> f(m + 1, vec<int>(m)), g(m + 1, vec<int>(m, -1));
        auto cmp = [&](int x, int y) { return !~x || !~y ? x < y : s[x].d < s[y].d; };
        r0p (i, n) g[s[i].l][s[i].r] = max(g[s[i].l][s[i].r], i, cmp);
        rep (L, 1, m - 1) rep (l, 1, m - L) {
            int r = l + L - 1; g[l][r] = max(g[l][r], max(g[l][r - 1], g[l + 1][r], cmp), cmp);
            int u = g[l][r]; if (!~u) continue;
            f[l][r] = inf;
            rep (i, s[u].l, s[u].r) f[l][r] = min(f[l][r], f[l][i - 1] + f[i + 1][r] + s[u].d);
        }
        cout << f[1][m - 1] << "\n";
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
