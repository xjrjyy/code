/* cf_1190_b.cpp */
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
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vec<int> a(n);
    each (x, a) cin >> x;
    sort(all(a));
    int qwq = 0;
    r0p (i, n - 1) if (a[i] == a[i + 1]) qwq += 1 + (a[i] == 0);
    if (qwq >= 2) return cout << "cslnb", 0;
    r0p (i, n - 2) if (a[i] + 1 == a[i + 1] && a[i + 1] == a[i + 2])
        return cout << "cslnb", 0;
    ll s = accumulate(all(a), 0ll), t = 0;
    int lst = -1;
    r0p (i, n) {
        int u = min(a[i], lst + 1);
        t += u, lst = u;
    }
    cout << ((s - t) % 2 ? "sjfnb" : "cslnb");
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
