/* cf_1463_f.cpp */
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
    const int inf = ~0u >> 2;
    int n, x, y; cin >> n >> x >> y; if (x > y) swap(x, y);
    int m = x + y, U = 1 << y, A = 0;
    vec<int> f(U, -inf), g(U); f[0] = 0;
    auto umx = [&](int &x, int y) { if (x < y) x = y; };
    r0p (i, m) {
        swap(f, g), fill(all(f), -inf);
        r0p (S, U) {
            int T = (S << 1) & (U - 1); umx(f[T], g[S]);
            if (~(S >> (x - 1)) & 1 && ~(S >> (y - 1)) & 1)
                umx(f[T ^ 1], g[S] + n / m + (i < n % m));
        }
        A = max(A, *max_element(all(f)));
    }
    cout << *max_element(all(f)) << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
