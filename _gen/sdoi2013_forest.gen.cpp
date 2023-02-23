/* sdoi2013_forest.gen.cpp */
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
mt19937 rnd;

const int maxn = 8e4 + 5;
int n = 20, q = 1000, fa[maxn];
vec<int> G[maxn]; set<int> S[maxn];
int fd(int x) { return fa[x] == x ? x : fa[x] = fd(fa[x]); }

int dfs(int u, int fa, int w) {
    int t; if (u == w) return 1;
    each (v, G[u]) if (v != fa && ~(t = dfs(v, u, w))) return t + 1;
    return -1;
}

int main(int argc, char *argv[]) {
    cin.tie(nullptr)->sync_with_stdio(false);
    assert(argc >= 2);
    rnd.seed(atoi(argv[1]));
    cout << 0 << endl << n << " 0 " << q << endl;
    vec<int> s(n);
    iota(all(s), 1), shuffle(all(s), rnd);
    each (x, s) cout << x << " ";
    cout << endl;
    rep (i, 1, n) fa[i] = i, S[i].insert(i);
    rep (_, 1, q) {
        int o = rnd() & 1, u = rnd() % n + 1, v;
        if (o == 0) {
            int w = fd(u); if (S[w].size() == n) { o = 1; goto a; }
            v = rnd() % (n - S[w].size()) + 1;
            auto it = S[w].begin();
            while (it != S[w].end() && *it <= v) ++it, ++v;
            cout << "L " << u << " " << v << "\n";
            u = w, v = fd(v); G[u].push_back(v), G[v].push_back(u);
            if (S[u].size() < S[v].size()) swap(u, v);
            S[u].insert(all(S[v])), fa[v] = u;
        }
        a:
        if (o == 1) {
            int w = fd(u), x = rnd() % S[w].size();
            auto it = S[w].begin();
            while (x--) ++it;
            v = *it;
            cout << "Q " << u << " " << v << " " << rnd() % dfs(u, -1, v) + 1 << "\n";
        }
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
