/* luogu_p9060.cpp */
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

const int maxn = 1e5 + 5;
const int mod = 998244353;
int power(int a, int b) {
    int c = 1;
    for (; b; b >>= 1, a = 1ll * a * a % mod) if (b & 1) c = 1ll * c * a % mod;
    return c;
}
int Inv(int x) { return power(x, mod - 2); }

struct opt { int l, r, i; };

int n, m, M, q, B, a[maxn], pos[maxn], inv[maxn], A[maxn];
opt Q[maxn];
vec<int> P;
void init(int n) {
    vec<int> vs(n + 1);
    rep (i, 2, n) if (!vs[i]) {
        P.push_back(i);
        for (int j = i + i; j <= n; j += i) vs[j] = 1;
    }
}

int pw(int x) { return 1ll * x * x % mod; }
int b[maxn], c[maxn], s[maxn];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q, B = max(int(n / sqrt(q)), 1);
    rep (i, 1, n) cin >> a[i], m = max(m, a[i]), pos[i] = (i - 1) / B + 1;
    rep (i, 1, q) cin >> Q[i].l >> Q[i].r, A[Q[i].i = i] = 1;
    inv[1] = 1; rep (i, 2, m) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    init(M = sqrt(m) + 1);
    each (p, P) {
        b[0] = p; rep (i, 1, n) b[i] = pw(b[i - 1]);
        for (int x = p; x <= m; x *= p) {
            rep (i, 1, n) s[i] = s[i - 1] + (a[i] % x == 0);
            rep (i, 1, q) A[i] = 1ll * A[i] * b[s[Q[i].r] - s[Q[i].l - 1]] % mod * inv[p] % mod;
        }
        rep (i, 1, n) while (a[i] % p == 0) a[i] /= p;
    }
    rep (i, 1, n) if (a[i] > 1) ++c[a[i]];
    rep (i, 1, m) if (c[i]) {
        s[b[i] = ++*b] = i;
        rep (j, 2, c[i]) ++*b, s[*b] = pw(s[*b - 1]);
        c[i] = 0;
    }

    sort(Q + 1, Q + q + 1, [&](const opt &x, const opt &y) {
        return pos[x.l] != pos[y.l] ? x.l < y.l : (pos[x.l] & 1) ? x.r < y.r : x.r > y.r;
    });
    int L = 1, R = 0, U = 1, D = 1;
    auto add = [&](int p) { if (a[p] > 1) U = 1ll * U * s[b[a[p]] + c[a[p]]++] % mod; };
    auto del = [&](int p) { if (a[p] > 1) D = 1ll * D * s[b[a[p]] + --c[a[p]]] % mod; };
    rep (i, 1, q) {
        auto &u = Q[i];
        while (R < u.r) add(++R);
        while (u.l < L) add(--L);
        while (u.r < R) del(R--);
        while (L < u.l) del(L++);
        A[u.i] = 1ll * A[u.i] * U % mod * Inv(D) % mod;
    }
    rep (i, 1, q) cout << A[i] << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
