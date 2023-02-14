/* luogu_p3939.cpp */
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

struct opt { int p, v; };

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n, m = 0, q; cin >> n >> q; const int B = sqrt(n) + 2;
    vec<int> a(n); each (x, a) cin >> x, m = max(m, x), --x;
    vec<vec<int>> b(m); vec<vec<opt>> s(m);
    auto bld = [&]() {
        r0p (i, m) b[i].clear(), s[i].clear();
        r0p (i, n) b[a[i]].push_back(i);
    };
    auto qry = [&](int c, int l, int r) {
        if (c >= m) return 0;
        int t = upper_bound(all(b[c]), r) - lower_bound(all(b[c]), l);
        each (x, s[c]) if (l <= x.p && x.p <= r) t += x.v;
        return t;
    };
    auto mdf = [&](int p, int q) {
        auto &x = s[a[p]], &y = s[a[q]]; swap(a[p], a[q]);
        x.push_back({p, -1}), x.push_back({q, 1});
        y.push_back({q, -1}), y.push_back({p, 1});
        if (int(x.size()) > B || int(y.size()) > B) bld();
    };
    bld();
    r0p (_, q) {
        int o, x, y, z; cin >> o >> x, --x;
        if (o == 1) cin >> y >> z, --y, --z, cout << qry(z, x, y) << '\n';
        if (o == 2) mdf(x, x + 1);
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
