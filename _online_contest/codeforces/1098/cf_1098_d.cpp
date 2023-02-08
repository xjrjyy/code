/* cf_1098_d.cpp */
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
    int n = 0, q; cin >> q; const int m = 32;
    vec<int> A(m); vec<ll> s(m); vec<multiset<int>> t(m);
    auto gps = [&](int x) {
        int p = 0; while ((1 << (p + 1)) <= x) ++p;
        return p;
    };
    auto upd = [&](int p) { A[p] = (s[p] && !t[p].empty() && s[p] * 2 < *t[p].begin()); };
    auto add = [&](int x) {
        int p = gps(x); ++n;
        t[p].insert(x), upd(p);
        while (++p < m) s[p] += x, upd(p);
    };
    auto del = [&](int x) {
        int p = gps(x); --n;
        t[p].erase(t[p].find(x)), upd(p);
        while (++p < m) s[p] -= x, upd(p);
    };
    r0p (_, q) {
        char o; int x; cin >> o >> x;
        if (o == '+') add(x);
        if (o == '-') del(x);
        cout << max(n - 1, 0) - accumulate(all(A), 0) << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
