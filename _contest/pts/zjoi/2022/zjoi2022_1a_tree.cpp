/* zjoi2022_1a_tree.cpp */
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

const int maxn = 5e2 + 5;

int n, m, f[maxn], a[maxn][maxn][maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m, a[1][1][1] = 1;
    rep (i, 2, n) {
        rep (j, 1, i) rep (k, 1, i) {
            int t = (0ll + a[i - 1][j - 1][k - 1] - a[i - 1][j - 1][k]
                - a[i - 1][j][k - 1] + 2 * a[i - 1][j][k] + m + m) % m;
            (f[i] += t) %= m, a[i][j][k] = 1ll * j * k % m * t % m;
        }
        cout << f[i] << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
