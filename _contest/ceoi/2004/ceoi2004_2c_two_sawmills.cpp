/* ceoi2004_2c_two_sawmills.cpp */
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

const int maxn = 2e4 + 5;
const ll inf = ~0ull >> 2;

int n; ll a[maxn], b[maxn], c[maxn], f[maxn], A = inf;

ll cost(int l, int r) {
    return c[r] - c[l - 1] - a[l - 1] * (b[r] - b[l - 1]);
}
void solve(int l, int r, int L, int R) {
    if (l > r) return;
    int m = (l + r) / 2, M = -1; f[m] = inf; ll t;
    rep (i, L, min(R, m - 1)) if ((t = c[i] + cost(i + 1, m)) < f[m]) f[m] = t, M = i;
    A = min(A, f[m] + cost(m + 1, n));
    solve(l, m - 1, L, M), solve(m + 1, r, M, R);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    rep (i, 1, n) cin >> a[i] >> b[i + 1], a[i] += a[i - 1];
    ++n;
    rep (i, 1, n) c[i] = c[i - 1] + a[i - 1] * b[i], b[i] += b[i - 1];
    solve(2, n, 1, n);
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
