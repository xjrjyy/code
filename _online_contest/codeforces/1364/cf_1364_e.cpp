/* cf_1364_e.cpp */
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

mt19937 rnd(time(0));

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n; const int m = 1 << 11, K = 20;
    vec<int> q(n); iota(all(q), 0), shuffle(all(q), rnd);
    auto rdf = [&](int x) {
        int y;
        do y = rnd() % n; while (y == x);
        return y;
    };
    auto qry = [&](int x, int y) {
        cout << "? " << q[x] + 1 << ' ' << q[y] + 1 << endl;
        int t; cin >> t; return t;
    };
    auto gvl = [&](int p) {
        int A = m - 1;
        r0p (_, K) A &= qry(p, rdf(p));
        return A;
    };
    int p = 0, x = gvl(p), L = 1;
    while (x) {
        if (x == qry(p, L)) p = L, x = gvl(p);
        ++L;
    }
    vec<int> A(n);
    r0p (i, n) if (p != i) A[q[i]] = qry(p, i);
    cout << "!"; each (x, A) cout << ' ' << x;
    cout << endl;
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
