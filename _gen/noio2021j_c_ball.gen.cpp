/* noio2021j_c_ball.gen.cpp */
#include <bits/stdc++.h>

#define fo(x) freopen(#x".in", "r", stdin); freopen(#x".out", "w", stdout);
#define rep(i, l, r) for (int i = l, rep##i = r; i <= rep##i; ++i)
#define per(i, r, l) for (int i = r, per##i = l; i >= per##i; --i)
#define r0p(i, r) rep (i, 0, (r) - 1)
#define p0r(i, l) per (i, (l) - 1, 0)
#define each(x, s) for (auto &x : s)
#define all(s) (s).begin(), (s).end()
#define dbg(x) (cerr << "Line#" << __LINE__ << " " << #x << "=" << (x) << endl)

using ll = long long; using ull = unsigned long long;
template <class T> using vec = std::vector<T>; using namespace std;
mt19937 rnd;

const int maxn = 2.5e3 + 5;

int n = 3, m = 2, q = 1, a[maxn][maxn];

void rnd_is(int &x, int &y, int t) {
	do x = rnd() % n + 1, y = rnd() % n + 1;
	while (a[x][y] != t);
}

int main(int argc, char *argv[]) {
    assert(argc >= 2);
    rnd.seed(atoi(argv[1]));
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cout << n << ' ' << m << ' ' << q << '\n';
	r0p (_, m) {
		int x, y;
		rnd_is(x, y, 0);
		a[x][y] = 1;
		cout << x << ' ' << y << '\n';
	}
	r0p (_, q) {
		int x, y;
		rnd_is(x, y, 0);
		cout << x << ' ' << y << ' ';
		rnd_is(x, y, 0);
		cout << x << ' ' << y << '\n';
	}
    // cerr << "\n" << double(clock()) / CLOCKS_PER_SEC << "s\n";
    return 0;
}
