/* cf_1198_c.cpp */
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
    vec<int> a(3 * n), A;
    r0p (i, m) {
        int u, v; cin >> u >> v, --u, --v;
        if (!a[u] && !a[v]) a[u] = a[v] = 1, A.push_back(i);
    }
    if (int(A.size()) >= n) {
        cout << "Matching\n";
        r0p (i, n) cout << A[i] + 1 << " \n"[i == repi];
    } else {
        A.clear(); r0p (i, 3 * n) if (!a[i]) A.push_back(i);
        cout << "IndSet\n";
        r0p (i, n) cout << A[i] + 1 << " \n"[i == repi];
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
