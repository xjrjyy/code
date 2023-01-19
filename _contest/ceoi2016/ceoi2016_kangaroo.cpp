/* ceoi2016_kangaroo.cpp */
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

const int maxn = 2e3 + 5;
const int mod = 1e9 + 7;

void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}

int n, s, t, f[maxn][maxn];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> s >> t;
    f[0][0] = 1;
    rep (i, 1, n) rep (j, 1, i) {
        if (i != s && i != t) {
            norm(f[i][j] += ll(f[i - 1][j + 1]) * j % mod);
            norm(f[i][j] += ll(f[i - 1][j - 1]) * (j - (i > s) - (i > t)) % mod);
        } else {
            norm(f[i][j] += f[i - 1][j]);
            norm(f[i][j] += f[i - 1][j - 1]);
        }
    }
    cout << f[n][1] << "\n";
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
