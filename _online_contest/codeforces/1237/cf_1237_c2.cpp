/* cf_1237_c2.cpp */
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

struct node {
    union {
        struct { int x, y, z; };
        int _[3];
    };
    int i;
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vec<node> a(n); vec<int> b;
    r0p (i, n) cin >> a[i].x >> a[i].y >> a[i].z, a[i].i = i;
    each (x, a) b.push_back(x.x), b.push_back(x.y), b.push_back(x.z);
    vec<pair<int, int>> A; using It = vec<node>::iterator;
    function<int(It, It, int)> solve = [&](It l, It r, int t) {
        if (t == 3) return l->i;
        sort(l, r, [&](const node &x, const node &y) { return x._[t] < y._[t]; });
        auto u = l; vec<int> s;
        while (u < r) {
            auto v = next(u);
            while (v != r && v->_[t] == u->_[t]) ++v;
            int o = solve(u, v, t + 1); u = v;
            if (~o) s.push_back(o);
        }
        for (int i = 0; i + 1 < int(s.size()); i += 2) A.push_back({s[i], s[i + 1]});
        return s.size() & 1 ? s.back() : -1;
    };
    solve(all(a), 0);
    each (x, A) cout << x.first + 1 << ' ' << x.second + 1 << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
