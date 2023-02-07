/* cf_1365_g.cpp */
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
    int n; cin >> n; const int m = 13, k = m / 2;
    vec<int> Q;
    r0p (i, (1 << m) - 1) if (__builtin_popcount(i) == k) Q.push_back(i);
    vec<int> A(63); ll B = 0;
    r0p (i, 13) {
        vec<int> q;
        r0p (j, n) if ((Q[j] >> i) & 1) q.push_back(j);
        if (q.empty()) continue;
        cout << "? " << q.size();
        each (x, q) cout << ' ' << x + 1;
        cout << endl;
        ll a; cin >> a;
        r0p (j, 63) if ((a >> j) & 1) A[j] |= (1 << i);
        B |= a;
    }
    vec<ll> C(n);
    r0p (i, n) r0p (j, 63) if (Q[i] == A[j]) C[i] |= (1ll << j);
    cout << '!';
    r0p (i, n) cout << ' ' << (B ^ C[i]);
    cout << endl;
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
