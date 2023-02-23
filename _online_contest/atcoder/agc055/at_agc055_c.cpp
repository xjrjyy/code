/* at_agc055_c.cpp */
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
    int n, m, mod; cin >> n >> m >> mod;
    auto norm = [&](int &x) {
        if (x >= mod) x -= mod;
        else if (x < 0) x += mod;
    };
    vec<array<int, 4>> f(m + 2), g = f;
    f[0][0] = 1;
    r0p (_, n) {
        swap(f, g); each (x, f) fill(all(x), 0);
        rep (i, 0, m) {
#define to(l, v, u) norm(f[l][v] += g[i][u])
            to(i + 1, 0, 0), to(i + 1, 1, 0), to(i, 2, 0);
            to(i, 0, 1);
            to(i + 1, 0, 2), to(i, 3, 2);
            to(i + 1, 3, 3), to(i, 3, 3);
        }
    }
    int A = 1;
    rep (i, 3, m) {
        norm(A += f[i][0]);
        norm(A += f[i][2]);
        norm(A += f[i][3]);
    }
    if (n != 3 && m == n - 1) ++A;
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
