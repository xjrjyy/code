/* cf_300_e.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = (l), rep##i = (r); i <= rep##i; ++i)
#define per(i, r, l) for (int i = (r), per##i = (l); i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : (s))
#define all(s) (s).begin(), (s).end()
#define dbg(x) (std::cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << std::endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>;

const int maxn = 1e7 + 5;
const int maxm = 1e6 + 5;

vec<int> P; int mp[maxn];
std::bitset<maxn> vs;
void init(int n) {
    rep (i, 2, n) {
        if (!vs[i]) P.push_back(i), mp[i] = i;
        each (p, P) {
            if (i * p > n) break;
            vs[i * p] = 1, mp[i * p] = p;
            if (i % p == 0) break;
        }
    }
}

int n, m, a[maxm]; ll c[maxn], b[maxn], S;

ll v(ll x, int p) {
    ll y = 0;
    while (x /= p) y += x;
    return y;
}

bool chk(ll o) {
    each (p, P) if (v(o, p) < b[p]) return false;
    return true;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> m;
    rep (i, 1, m) std::cin >> a[i], n = std::max(a[i], n), c[a[i]] += 1, S += a[i];
    init(n);
    per (i, n, 1) c[i] += c[i + 1];
    per (i, n, 2) b[mp[i]] += c[i], c[i / mp[i]] += c[i];
    ll L = 1, R = S, M, A = -1;
    while (L <= R) {
        if (chk(M = (L + R) / 2)) A = M, R = M - 1;
        else L = M + 1;
    }
    std::cout << A << '\n';
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
