/* cf_889_e.cpp */
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
    int n; cin >> n;
    vec<ll> a(n); each (x, a) cin >> x;
    map<ll, ll> f; f[a[0] - 1] = 0;
    rep (i, 1, n - 1) {
        if (a[i] >= a[i - 1]) continue;
        for (auto x = f.lower_bound(a[i]); x != f.end(); ++x) {
            ll y = x->first % a[i], &t = f[y], &o = f[a[i] - 1];
            t = max(t, x->second + (x->first - y) * i);
            o = max(o, x->second + ((x->first + 1) / a[i] * a[i] - a[i]) * i);
        }
        f.erase(f.lower_bound(a[i]), f.end());
    }
    ll A = 0;
    each (x, f) A = max(A, x.second + x.first * n);
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
