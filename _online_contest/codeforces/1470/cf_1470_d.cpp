/* cf_1470_d.cpp */
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

void solve() {
    int n, m; cin >> n >> m;
    vec<vec<int>> G(n);
    r0p (_, m) {
        int u, v; cin >> u >> v, --u, --v;
        G[u].push_back(v), G[v].push_back(u);
    }
    vec<int> a(n), b(n); queue<int> Q;
    a[0] = 1, Q.push(0);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop(), b[u] = 1;
        each (v, G[u]) b[u] &= (!a[v] || !b[v]);
        each (v, G[u]) if (!a[v]) a[v] = 1, Q.push(v);
    }
    if (any_of(all(a), [](int x) { return !x; })) return cout << "NO\n", void();
    vec<int> A;
    r0p (u, n) if (b[u]) A.push_back(u);
    cout << "YES\n" << int(A.size()) << '\n';
    r0p (i, int(A.size())) cout << A[i] + 1 << " \n"[i == repi];
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
