/* cf_1404_d.cpp */
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
    int n; cin >> n;
    if (~n & 1) {
        cout << "First" << endl;
        rep (i, 1, 2 * n) cout << (i - 1) % n + 1 << ' ';
        cout << endl;
        return 0;
    }
    cout << "Second" << endl;
    vec<int> a(n + 1), to(2 * n + 1);
    rep (i, 1, 2 * n) {
        int x; cin >> x;
        if (a[x]) to[a[x]] = i, to[i] = a[x];
        else a[x] = i;
    }
    vec<int> vs(2 * n + 1), A, B;
    auto rev = [&](int x) { return x <= n ? x + n : x - n; };
    function<void(int)> dfs = [&](int u) {
        vs[u] = vs[to[u]] = 1, A.push_back(u), B.push_back(to[u]);
        if (!vs[rev(u)]) dfs(to[rev(u)]);
    };
    rep (i, 1, n) if (!vs[i]) dfs(i);
    if (accumulate(all(A), 0ll) % (2 * n)) swap(A, B);
    each (x, A) cout << x << ' ';
    cout << endl;
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
