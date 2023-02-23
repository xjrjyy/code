/* cf_1190_a.cpp */
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
    ll n, k; int m; cin >> n >> m >> k;
    vec<ll> a(m); each (x, a) cin >> x, --x;
    sort(all(a));
    int A = 0;
    for (int l = 0, r; l < m; l = r + 1) {
        r = l;
        while (r + 1 < m && (a[r + 1] - l) / k == (a[l] - l) / k) ++r;
        ++A;
    }
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
