/* thusc2015_xor.cpp 异或运算 */
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

const int maxn = 1e3 + 5;
const int maxm = 3e5 + 5;
const int maxw = 33;

struct Node { int ch[2], sz; };

int n, m, q, w = 31, a[maxn], b[maxm];
Node s[maxm * maxw]; int rt[maxm], tt;

void bld(int &u, int v, int x, int p) {
    s[u = ++tt] = s[v], s[u].sz += 1;
    if (p < 0) return;
    int t = (x >> p) & 1;
    bld(s[u].ch[t], s[v].ch[t], x, p - 1);
}
int qry(int l, int r, int L, int R, int k) {
    static int u[maxn], v[maxn];
    rep (i, l, r) u[i] = rt[R], v[i] = rt[L - 1];
    int A = 0;
    per (i, w, 0) {
        int o = 0;
        rep (j, l, r) {
            int t = ~(a[j] >> i) & 1;
            o += s[s[u[j]].ch[t]].sz - s[s[v[j]].ch[t]].sz;
        }
        int p = o < k; A ^= !p << i, k -= p * o;
        rep (j, l, r) {
            int t = ~(a[j] >> i) & 1; t ^= p;
            u[j] = s[u[j]].ch[t], v[j] = s[v[j]].ch[t];
        }
    }
    return A;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    rep (i, 1, n) cin >> a[i];
    rep (i, 1, m) cin >> b[i], bld(rt[i], rt[i - 1], b[i], w);
    cin >> q;
    rep (_, 1, q) {
        int l, r, L, R, k; cin >> l >> r >> L >> R >> k;
        cout << qry(l, r, L, R, k) << "\n";
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
