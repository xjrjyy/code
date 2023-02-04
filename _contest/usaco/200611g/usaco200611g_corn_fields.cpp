/* usaco200611g_corn_fields.cpp */
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

#define forS(T, S) for (int cur##T = (S), T = cur##T; T; T = (T - 1) & cur##T)
const int mod = 1e8;

void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m, U; cin >> n >> m, U = 1 << m;
    vec<int> a(n);
    r0p (i, n) r0p (j, m) { int x; cin >> x; a[i] |= (!x << j); }
    vec<int> f(U), g(U), F; f[0] = 1;
    r0p (S, U) if ((S & (S << 1)) == 0) F.push_back(S);
    r0p (i, n) {
        swap(f, g), fill(all(f), 0);
        each (S, F) if ((S & a[i]) == 0) {
            forS (T, (U - 1) ^ S) norm(f[S] += g[T]);
            norm(f[S] += g[0]);
        }
    }
    cout << accumulate(all(f), 0ll) % mod << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
