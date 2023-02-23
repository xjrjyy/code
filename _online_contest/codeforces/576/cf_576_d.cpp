/* cf_576_d.cpp */
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

const int maxn = 1.5e2 + 5;
int n;
using Vec = bitset<maxn>;
struct Mat {
    bitset<maxn> a[maxn];
    Mat() {}
    bitset<maxn> &operator[](std::size_t p) { return a[p]; }
    const bitset<maxn> &operator[](std::size_t p) const { return a[p]; }
    friend Mat operator*(const Mat &x, const Mat &y) {
        Mat z; r0p (i, n) r0p (k, n) if (x[i][k]) z[i] |= y[k];
        return z;
    }
    friend Vec operator*(const Mat &x, const Vec &y) {
        Vec z; r0p (k, n) z[k] = (x[k] & y).any();
        return z;
    }
};

struct edge { int u, v, w; };
bool operator<(const edge &x, const edge &y) { return x.w < y.w; }
void power(Mat a, int b, Vec &c) {
    for (; b; b >>= 1, a = a * a) if (b & 1) c = a * c;
}

int main() {
    const int inf = ~0u >> 2;
    cin.tie(nullptr)->sync_with_stdio(false);
    int m; cin >> n >> m;
    vec<edge> E(m); each (e, E) cin >> e.u >> e.v >> e.w, --e.u, --e.v;
    sort(all(E));
    int t = 0, A = inf;
    Vec v; v[0] = 1;
    Mat G;
    auto upd = [&]() {
        queue<int> Q; vec<int> d(n, inf);
        r0p (i, n) if (v[i]) Q.push(i), d[i] = 0;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            r0p (v, n) if (d[v] > d[u] + 1 && G[v][u])
                d[v] = d[u] + 1, Q.push(v);
        }
        A = min(A, t + d[n - 1]);
    };
    each (e, E) {
        int o = e.w - t;
        power(G, o, v);
        t = e.w, G[e.v][e.u] = 1;
        upd();
    }
    if (A == inf) cout << "Impossible\n";
    else cout << A << '\n';
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
