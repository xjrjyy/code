/* cf_1574_f.cpp */
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
    const int mod = 998244353;
    auto norm = [&](int &x) {
        if (x >= mod) x -= mod;
        else if (x < 0) x += mod;
    };
    int n, m, k; cin >> n >> m >> k;
    vec<int> L(k), R(k), fa(k); iota(all(fa), 0);
    function<int(int)> fd = [&](int u) { return u == fa[u] ? u : fa[u] = fd(fa[u]); };
    vec<int> a(k, 1), b(k + 1), to(k, -1);
    r0p (_, n) {
        int t; cin >> t;
        vec<int> s(t); each (x, s) cin >> x, --x;
        r0p (i, t - 1) {
            int u = s[i], v = s[(i + 1) % t];
            if (to[u] == v) continue;
            to[u] = v, ++R[u], ++L[v]; int x = fd(u), y = fd(v);
            if (x == y || max(max(L[u], R[u]), max(L[v], R[v])) > 1) a[y] = -1;
            a[x] = (min(a[x], a[y]) == -1 ? -1 : a[x] + a[y]);
            fa[y] = x;
        }
    }
    r0p (i, k) if (fd(i) == i && ~a[i]) b[a[i]] += 1;
    vec<int> T;
    rep (i, 1, k) if (b[i]) T.push_back(i);
    vec<int> f(m + 1); f[0] = 1;
    rep (i, 0, m) each (x, T) if (i >= x) norm(f[i] += ll(f[i - x]) * b[x] % mod);
    cout << f[m] << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
