/* luogu_p5239.cpp */
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

const int maxn = 1e3 + 5;
const int mod = 19260817;

void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}

int C[maxn][maxn];

void init(int n) {
    rep (i, 0, n) C[i][0] = 1;
    rep (i, 1, n) rep (j, 1, i) norm(C[i][j] = C[i - 1][j] + C[i - 1][j - 1]);
    rep (i, 0, n) C[i][0] = 0;
    rep (i, 0, n) rep (j, 1, n) norm(C[i][j] += C[i][j - 1]);
    rep (i, 1, n) rep (j, 0, n) norm(C[i][j] += C[i - 1][j]);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    init(maxn - 5);
    int q; cin >> q;
    rep (_, 1, q) {
        int n, m; cin >> m >> n;
        cout << C[n][m] << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
