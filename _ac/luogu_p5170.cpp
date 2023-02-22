/* luogu_p5170.cpp */
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

const int mod = 998244353;

struct Node {
    int u, r, A, B, C;
    Node(int u_, int r_, int A_, int B_, int C_) : u(u_), r(r_), A(A_), B(B_), C(C_) {}
    Node() : Node(0, 0, 0, 0, 0) {}
    static Node U() { return Node(1, 0, 0, 0, 0); }
    static Node R() { return Node(0, 1, 0, 0, 0); }
    friend Node operator*(const Node &x, const Node &y) {
        int u = (x.u + y.u) % mod, r = (x.r + y.r) % mod;
        int A = (1ll * x.u * y.r + x.A + y.A) % mod;
        int B = (2ll * x.u * y.A + 1ll * x.u * x.u % mod * y.r + x.B + y.B) % mod;
        int i = 1ll * y.r * (y.r + 1) / 2 % mod;
        int C = (1ll * x.u * i + 1ll * x.r * y.A + 1ll * x.u * x.r % mod * y.r + x.C + y.C) % mod;
        return Node(u, r, A, B, C);
    }
};

template <typename T> T power(T a, ll b) {
    T c; for (; b; b >>= 1, a = a * a) if (b & 1) c = c * a;
    return c;
}
ll F(ll p, ll r, ll q, ll x) { return ((long double)p * x + r) / q; }
template <typename T> T eud(ll p, ll r, ll q, ll l, const T &U, const T &R) {
    if (!l) return T();
    if (p >= q) return eud(p % q, r, q, l, U, power(U, p / q) * R);
    ll m = F(p, r, q, l); if (!m) return power(R, l);
    ll u = (q - r - 1) / p, v = l - F(q, -r - 1, p, m);
    return power(R, u) * U * eud(q, (q - r - 1) % p, p, m - 1, R, U) * power(R, v);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        ll n, p, r, q; cin >> n >> p >> r >> q;
        Node U = Node::U(), R = Node::R();
        Node A = power(U, r / q) * eud(p, r % q, q, n, U, R);
        int v = r / q;
        cout << (A.A + v) % mod << ' ' << (A.B + 1ll * v * v) % mod << ' ' << A.C << '\n';
    }
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
