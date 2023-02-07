/* cf_1450_c2.cpp */
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

void solve() {
    const vec<int> Dx = {-1, 0, 0, 1}, Dy = {0, -1, 1, 0};
    int n; cin >> n;
    vec<string> a(n), A; each (x, a) cin >> x;
    int mx = -1;
    auto upd = [&](const vec<string> &B) {
        int t = 0;
        r0p (i, n) r0p (j, n) t += (a[i][j] != B[i][j]);
        if (A.empty() || t < mx) A = B, mx = t;
    };
    r0p (o, 3) {
        vec<string> b(a);
        r0p (i, n) r0p (j, n) if (b[i][j] != '.') {
            int t = (i + j + o) % 3;
            if (t == 0) b[i][j] = 'O';
            if (t == 1) b[i][j] = 'X';
        }
        upd(b);
    }
    each (x, A) cout << x << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T; cin >> T;
    while (T--) solve();
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
