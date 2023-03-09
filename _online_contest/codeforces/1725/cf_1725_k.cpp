/* cf_1725_k.cpp */
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

struct DSU {
    int n; vec<int> fa;
    DSU(int n_) : n(n_), fa(n) { std::iota(all(fa), 0); }
    int fd(int x) { return x == fa[x] ? x : fa[x] = fd(fa[x]); }
    bool same(int x, int y) { return fd(x) == fd(y); }
    void mg(int u, int v) {
        if ((u = fd(u)) == (v = fd(v))) return;
        fa[v] = u;
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; std::cin >> n;
    vec<int> a(n); each (x, a) std::cin >> x;
    int q; std::cin >> q;

    vec<int> cur(n), val(n + 2 * q); DSU dsu(n + 2 * q);
    std::map<int, int> pos; int cnt = 0;
    auto ins = [&](int p, int x) {
        val[cur[p] = cnt++] = x;
        if (pos.count(x)) dsu.mg(pos[x], cur[p]);
        else pos[x] = cur[p];
    };
    r0p (i, n) ins(i, a[i]);

    r0p (_, q) {
        int o, x, y; std::cin >> o >> x;
        if (o == 1) std::cin >> y, --x, ins(x, y);
        if (o == 2) --x, std::cout << val[dsu.fd(cur[x])] << '\n';
        if (o == 3) {
            std::cin >> y;
            for (auto it = pos.lower_bound(x); it != pos.end() && it->first <= y; it = pos.erase(it)) {
                int v = it->first - x < y - it->first ? x - 1 : y + 1;
                if (!pos.count(v)) val[pos[v] = cnt++] = v;
                dsu.mg(pos[v], it->second);
            }
        }
    }
    // std::cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
