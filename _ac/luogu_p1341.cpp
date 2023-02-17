/* luogu_p1341.cpp */
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
    int n = 52, m; cin >> m;
    auto id = [&](char c) -> int { return isupper(c) ? c - 'A' : c - 'a' + 26; };
    auto nam = [&](int x) -> char { return x < 26 ? x + 'A' : x - 26 + 'a'; };
    vec<vec<pair<int, int>>> G(n);
    r0p (i, m) {
        string s; cin >> s; int u = id(s[0]), v = id(s[1]);
        G[u].push_back({v, i}), G[v].push_back({u, i});
    }
    int s = -1, tt = 0;
    r0p (u, n) {
        sort(all(G[u]));
        if (int(G[u].size()) & 1) {
            ++tt;
            if (!~s) s = u;
        }
    }
    if (tt != 0 && tt != 2) return cout << "No Solution\n", 0;
    if (!tt) r0p (u, n) if (!G[u].empty()) { s = u; break; }
    vec<int> h(n);
    vec<int> vs(m); string A;
    function<void(int)> dfs = [&](int u) {
        for (int &i = h[u]; i < int(G[u].size()); ++i) {
            int v = G[u][i].first, w = G[u][i].second;
            if (!vs[w]) vs[w] = 1, dfs(v);
        }
        A.push_back(nam(u));
    };
    dfs(s); reverse(all(A));
    if (int(A.size()) < m + 1) A = "No Solution";
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
