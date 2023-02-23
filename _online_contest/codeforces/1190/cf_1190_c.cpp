/* cf_1190_c.cpp */
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
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vec<int> a(n + 1); r0p (i, n) a[i + 1] = a[i] + (s[i] - '0');
    auto qry = [&](int l, int r) { return a[r] - a[l - 1]; };
    rep (i, 1, n - k + 1) {
        int x = qry(1, i - 1) + qry(i + k, n);
        if (x == 0 || x == n - k) return cout << "tokitsukaze", 0;
    }
    if (k == 1) return cout << "once again", 0;
    bool fl = true;
    auto als = [&](int l, int r, int k) { return qry(l, r) == k * (r - l + 1); };
    vec<int> ps[2];
    r0p (i, n) ps[s[i] - '0'].push_back(i + 1);
    auto chk = [&](int o, int l, int r) -> bool {
        auto &p = ps[o];
        if (als(1, l - 1, o)) {
            auto x = lower_bound(all(p), r + 1);
            if (x == p.end() || p.back() - *x + 1 <= k) return true;
        }
        if (als(r + 1, n, o)) {
            auto x = lower_bound(all(p), l);
            if (x == p.begin() || *prev(x) - p.front() + 1 <= k) return true;
        }
        return false;
    };
    r0p (o, 2) rep (i, 1, n - k + 1) if (!chk(o, i, i + k - 1)) { fl = false; break; }
    if (fl) return cout << "quailty", 0;
    cout << "once again";
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
