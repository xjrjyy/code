/* zjoi2019_1a_mahjong.cpp */
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

template <typename T> void umax(T &x, const T &y) { if (x < y) x = y; }

const int maxN = 2345;

struct Data {
    int f[3][3];
    Data() { r0p (i, 3) r0p (j, 3) f[i][j] = -1; }
    int *operator[](std::size_t p) { return f[p]; }
    const int *operator[](std::size_t p) const { return f[p]; }
    Data operator+(int y) const {
        Data z;
        r0p (i, 3) r0p (j, 3) if (~f[i][j]) r0p (k, 3) if (y >= i + j + k)
            umax(z[j][k], min(f[i][j] + i + (y - i - j - k) / 3, 4));
        return z;
    }
    Data &operator*=(const Data &y) {
        r0p (i, 3) r0p (j, 3) umax(f[i][j], y[i][j]);
        return *this;
    }
};

struct Node {
    int ct; Data a[2];
    Node(int c = 0) : ct(c) { a[0] = a[1] = Data(); }
    static Node win() { return Node(114514); }
    bool is_win() const { return ct == 114514; }
    bool operator<(const Node &y) const {
        r0p (t, 2) r0p (i, 3) r0p (j, 3)
            if (a[t][i][j] != y.a[t][i][j]) return a[t][i][j] < y.a[t][i][j];
        return ct < y.ct;
    }
    Node operator+(int y) const {
        Node z(ct + (y >= 2)); if (z.ct >= 7) return win();
        r0p (i, 2) z.a[i] = a[i] + y;
        if (y >= 2) z.a[1] *= a[0] + (y - 2);
        r0p (i, 3) r0p (j, 3) if (z.a[1][i][j] >= 4) return win();
        return z;
    }
};

queue<Node> Q;
map<Node, int> M; int N, td;
set<std::size_t> A;
int G[maxN][5];
void init() {
    Node s(0); s.a[0][0][0] = 0;
    M[s] = N++, Q.push(s);
    while (!Q.empty()) {
        Node u = Q.front(); Q.pop();
        rep (i, 0, 4) {
            Node v = u + i;
            if (!M.count(v)) {
                if (v.is_win()) td = N;
                M[v] = N++, Q.push(v);
            }
            G[M[u]][i] = M[v];
        }
    }
}

const int mod = 998244353;
const int maxm = 4e2 + 5;
void norm(int &x) {
    if (x >= mod) x -= mod;
    else if (x < 0) x += mod;
}
int qpow(int x, int y) {
	if(x == 0) return 0;
	int res = 1;
	for(; y; x = 1ll * x * x % mod, y >>= 1) if(y & 1) res = 1ll * res * x % mod;
	return res;
}
int inv(int x) { return qpow(x, mod - 2); }

int fac[maxm], ifac[maxm];
void init(int n) {
    fac[0] = 1; rep (i, 1, n) fac[i] = ll(fac[i - 1]) * i % mod;
    ifac[n] = inv(fac[n]); per (i, n, 1) ifac[i - 1] = ll(ifac[i]) * i % mod;
}
int C(int n, int m) { return n < m ? 0 : ll(fac[n]) * ifac[m] % mod * ifac[n - m] % mod; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    init();
    int n, m; cin >> n, m = 4 * n - 13, init(m);
    vec<int> a(n);
    r0p (_, 13) { int p, x; cin >> p >> x, --p, a[p] += 1; }
    vec<vec<int>> f(m + 1, vec<int>(N)), g = f; f[0][0] = 1;
    r0p (i, n) {
        swap(f, g); each (x, f) fill(all(x), 0);
        rep (j, 0, i * 4) rep (k, 0, min(4 - a[i], m - j)) r0p (u, N)
            norm(f[j + k][G[u][a[i] + k]] += ll(g[j][u]) * C(4 - a[i], k) % mod);
    }
    int A = 0;
    r0p (i, m) r0p (u, N) if (u != td) norm(A += ll(f[i][u]) * inv(C(m, i)) % mod);
    cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
