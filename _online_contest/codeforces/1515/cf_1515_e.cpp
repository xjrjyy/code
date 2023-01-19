/* cf_1515_e.cpp */
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

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, p; cin >> n >> p;
    auto norm = [p](int &x) {
        if (x >= p) x -= p;
        else if (x < 0) x += p;
    };
    vec<vec<int>> f(n + 1, vec<int>(n + 1));
    f[0][0] = 1;
    rep (i, 1, n) rep (j, 1, i) {
        f[i][j] = 1ll * f[i - 1][j - 1] * j % p;
        norm(f[i][j] += 2ll * f[i - 1][j] * j % p);
        if (i > 2) norm(f[i][j] += 2ll * f[i - 2][j] * j % p);
        if (i > 2 && j + 1 <= i - 2) norm(f[i][j] += 2ll * f[i - 2][j + 1] * j % p);
        if (i > 3 && j + 1 <= i - 3) norm(f[i][j] += 1ll * f[i - 3][j + 1] * j % p);
    }
    cout << f[n][1] << "\n";
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
