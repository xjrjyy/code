/* apio2019_bridge.gen.cpp */
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
mt19937 rnd;

struct edge { int u, v, w; };

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    assert(argc >= 2);
    rnd.seed(atoi(argv[1]));
    int n = 5, m = 7, q = 4;
	cout << n << ' ' << m << '\n';
	auto rdw = [&]() { return int(rnd() % 10) + 1; };
	vec<edge> E;
	rep (u, 1, n - 1) E.push_back({int(rnd() % u), u, rdw()});
	while (int(E.size()) < m) {
		int u = rnd() % n, v;
		do v = rnd() % n; while (u == v);
		E.push_back({u, v, rdw()});
	}
	each (x, E) cout << x.u + 1 << ' ' << x.v + 1 << ' ' << x.w << '\n';
	cout << q << '\n';
	r0p (_, q) {
		int o = rnd() % 2 + 1, x, y;
		if (o == 1) x = rnd() % m, y = rdw();
		if (o == 2) x = rnd() % n, y = rdw();
		cout << o << ' ' << x + 1 << ' ' << y << '\n';
	}
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
