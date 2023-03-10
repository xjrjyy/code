/* cf_1327_g.cpp */
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

const int maxn = 1e3 + 5;

struct ACAM {
    int a[maxn], t[maxn][14], fa[maxn], tt;
    int touch(int u, int c) { if (!t[u][c]) { t[u][c] = ++tt; } return t[u][c]; }
    void ins(const std::string &s, int x) {
        int u = 0;
        each (c, s) u = touch(u, c - 'a');
        a[u] += x;
    }
    void bld() {
        std::queue<int> Q;
        r0p (i, 14) if (t[0][i]) Q.push(t[0][i]);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            r0p (i, 14) {
                if (t[u][i]) fa[t[u][i]] = t[fa[u]][i], Q.push(t[u][i]);
                else t[u][i] = t[fa[u]][i];
            }
        }
    }
} ac;

int n, m, q, k, pos[14]; std::string s;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> q;
    r0p (_, q) { int x; std::cin >> s >> x, ac.ins(s, x), k = std::max(k, int(s.size())); }
    ac.bld();
    std::cin >> s, n = int(s.size());
    r0p (i, n) if (s[i] == '?') pos[m++] = i;


    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
