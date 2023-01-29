/* jsoi2014_connect.cpp 强连通图 */
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

const int maxn = 1e5 + 5;

int n, m;
vec<int> G[maxn], g[maxn];

int dfn[maxn], low[maxn], vs[maxn], S[maxn], scn[maxn], A, B;
void tarjan(int u) {
    dfn[u] = low[u] = ++*dfn, vs[u] = true, S[++*S] = u;
    each (v, G[u]) {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (vs[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++*scn; int tt = 0;
        for (int v = S[*S]; S[*S + 1] != u; v = S[--*S])
            vs[v] = false, scn[v] = *scn, ++tt;
        A = max(A, tt);
    }
}
int ind[maxn], outd[maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    rep (i, 1, m) {
        int u, v; cin >> u >> v;
        G[u].push_back(v);
    }
    rep (i, 1, n) if (!dfn[i]) tarjan(i);
    rep (u, 1, n) each (v, G[u]) if (scn[u] != scn[v]) ++outd[scn[u]], ++ind[scn[v]];
    n = *scn;
    int x = 0, y = 0;
    rep (i, 1, n) x += !ind[i], y += !outd[i];
    if (n > 1) B = max(x, y);
    cout << A << '\n' << B << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
