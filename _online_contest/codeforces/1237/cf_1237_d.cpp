/* cf_1237_d.cpp */
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
    vec<int> a(n); each (x, a) cin >> x;
    if (*min_element(all(a)) * 2 >= *max_element(all(a))) {
        r0p (i, n) cout << -1 << ' ';
        return 0;
    }
    a.insert(a.end(), all(a)), a.push_back(~0u >> 2); int m = int(a.size());
    vec<int> s(m << 2), t(m << 2);
    function<void(int, int, int)> bld = [&](int u, int l, int r) {
        if (r - l == 1) return s[u] = t[u] = a[l], void();
        int mid = (l + r) / 2, ls = u << 1, rs = ls | 1;
        bld(ls, l, mid), bld(rs, mid, r);
        s[u] = max(s[ls], s[rs]), t[u] = min(t[ls], t[rs]);
    };
    bld(1, 0, m);
    function<int(int, int, int, int, int)> qmx = [&](int u, int l, int r, int p, int x) {
        if (s[u] < x) return -1;
        if (r - l == 1) return l;
        int mid = (l + r) / 2, ls = u << 1, rs = ls | 1, A = -1;
        if (p < mid) A = qmx(ls, l, mid, p, x);
        if (!~A) A = qmx(rs, mid, r, p, x);
        return A;
    };
    function<int(int, int, int, int, int)> qmn = [&](int u, int l, int r, int p, int x) {
        if (t[u] > x) return -1;
        if (r - l == 1) return l;
        int mid = (l + r) / 2, ls = u << 1, rs = ls | 1, A = -1;
        if (p < mid) A = qmn(ls, l, mid, p, x);
        if (!~A) A = qmn(rs, mid, r, p, x);
        return A;
    };
    vec<int> A(n);
    r0p (i, n) {
        int u = qmx(1, 0, m, i + 1, a[i] + 1);
        int v = qmn(1, 0, m, i + 1, (a[i] + 1) / 2 - 1);
        if (u < v) A[i] = -u;
        else A[i] = v - i;
    }
    function<int(int)> qry = [&](int u) {
        return A[u] > 0 ? A[u] : (A[u] = qry(-A[u] % n) + -A[u] - u);
    };
    r0p (i, n) cout << qry(i) << ' ';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
