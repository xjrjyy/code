/* at_arc127_e.cpp */
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

const int mod = 998244353;
void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k = 0; cin >> n >> m;
    vec<int> a;
    r0p (_, n + m) {
        int x; cin >> x;
        if (x == 1) a.push_back(++k);
        else a.pop_back();
    }
    vec<vec<int>> f(n - m + 1, vec<int>(n + m + 1));
    fill(all(f[0]), 1);
    rep (i, 1, n - m) {
        rep (j, 1, a[i - 1]) f[i][j] = f[i - 1][j - 1];
        rep (j, 1, n + m) norm(f[i][j] += f[i][j - 1]);
    }
    cout << f[n - m][n + m];
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
